// Lodestone Night Pod beacon firmware (ESP32-C3 SuperMini)
// Broadcasts an iBeacon so the iPhone app can tell when you're in the room.
// Settings are changed over USB serial (115200 baud) and saved to flash.
//
// SPDX-License-Identifier: CERN-OHL-S-2.0

#include <NimBLEDevice.h>
#include <Preferences.h>

static const char* DEFAULT_UUID = "A4BA2C0E-C9E0-4EFD-ACDC-0A8E782A5F81";
static const int LED_PIN = 8;               // SuperMini blue LED, active LOW
static const uint16_t ADV_INTERVAL = 480;   // x 0.625 ms = 300 ms

Preferences prefs;

struct Settings {
  String uuid;
  uint16_t major;
  uint16_t minor;
  int8_t txPower;       // radio power in dBm (-24 .. +20 on ESP32-C3)
  int8_t measuredPower; // expected RSSI at 1 m, used by iOS for distance
} cfg;

static bool parseUuid(const String& text, uint8_t out[16]) {
  String hex = text;
  hex.replace("-", "");
  if (hex.length() != 32) return false;
  for (int i = 0; i < 16; i++) {
    char buf[3] = {hex[i * 2], hex[i * 2 + 1], 0};
    char* end;
    long v = strtol(buf, &end, 16);
    if (*end != 0) return false;
    out[i] = (uint8_t)v;
  }
  return true;
}

static void loadSettings() {
  prefs.begin("lodestone", true);
  cfg.uuid = prefs.getString("uuid", DEFAULT_UUID);
  cfg.major = prefs.getUShort("major", 1);
  cfg.minor = prefs.getUShort("minor", 1);
  cfg.txPower = prefs.getChar("tx", -12);
  cfg.measuredPower = prefs.getChar("mp", -70);
  prefs.end();
}

static void saveSettings() {
  prefs.begin("lodestone", false);
  prefs.putString("uuid", cfg.uuid);
  prefs.putUShort("major", cfg.major);
  prefs.putUShort("minor", cfg.minor);
  prefs.putChar("tx", cfg.txPower);
  prefs.putChar("mp", cfg.measuredPower);
  prefs.end();
}

static void startAdvertising() {
  uint8_t uuid[16];
  if (!parseUuid(cfg.uuid, uuid)) {
    Serial.println("Stored UUID is invalid, using default");
    cfg.uuid = DEFAULT_UUID;
    parseUuid(cfg.uuid, uuid);
  }

  // Apple iBeacon layout: company 0x004C, type 0x02, length 0x15,
  // UUID (16), major (2, big-endian), minor (2, big-endian), measured power (1)
  std::vector<uint8_t> data = {0x4C, 0x00, 0x02, 0x15};
  data.insert(data.end(), uuid, uuid + 16);
  data.push_back(cfg.major >> 8);
  data.push_back(cfg.major & 0xFF);
  data.push_back(cfg.minor >> 8);
  data.push_back(cfg.minor & 0xFF);
  data.push_back((uint8_t)cfg.measuredPower);

  NimBLEAdvertisementData adv;
  adv.setFlags(BLE_HS_ADV_F_BREDR_UNSUP);
  adv.setManufacturerData(data);

  NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
  advertising->stop();
  NimBLEDevice::setPower(cfg.txPower);
  advertising->setConnectableMode(BLE_GAP_CONN_MODE_NON);
  advertising->setMinInterval(ADV_INTERVAL);
  advertising->setMaxInterval(ADV_INTERVAL);
  advertising->setAdvertisementData(adv);
  advertising->start();
}

static void printStatus() {
  Serial.println("Lodestone Night Pod beacon");
  Serial.printf("  uuid   %s\n", cfg.uuid.c_str());
  Serial.printf("  major  %u\n", cfg.major);
  Serial.printf("  minor  %u\n", cfg.minor);
  Serial.printf("  tx     %d dBm (radio reports %d)\n", cfg.txPower, NimBLEDevice::getPower());
  Serial.printf("  mp     %d dBm at 1 m\n", cfg.measuredPower);
  Serial.println("Commands: status | tx <dBm> | mp <dBm> | major <n> | minor <n> | uuid <uuid> | reset");
}

static void handleCommand(String line) {
  line.trim();
  if (line.length() == 0) return;
  int space = line.indexOf(' ');
  String cmd = space < 0 ? line : line.substring(0, space);
  String arg = space < 0 ? "" : line.substring(space + 1);
  arg.trim();
  cmd.toLowerCase();

  if (cmd == "status") {
    printStatus();
    return;
  }
  if (cmd == "tx") {
    long v = arg.toInt();
    if (arg.length() == 0 || v < -24 || v > 20) { Serial.println("tx must be -24 .. 20"); return; }
    cfg.txPower = (int8_t)v;
  } else if (cmd == "mp") {
    long v = arg.toInt();
    if (arg.length() == 0 || v < -100 || v > 0) { Serial.println("mp must be -100 .. 0"); return; }
    cfg.measuredPower = (int8_t)v;
  } else if (cmd == "major" || cmd == "minor") {
    long v = arg.toInt();
    if (arg.length() == 0 || v < 0 || v > 65535) { Serial.println("value must be 0 .. 65535"); return; }
    if (cmd == "major") cfg.major = (uint16_t)v; else cfg.minor = (uint16_t)v;
  } else if (cmd == "uuid") {
    uint8_t tmp[16];
    if (!parseUuid(arg, tmp)) { Serial.println("uuid must look like A4BA2C0E-C9E0-4EFD-ACDC-0A8E782A5F81"); return; }
    arg.toUpperCase();
    cfg.uuid = arg;
  } else if (cmd == "reset") {
    prefs.begin("lodestone", false);
    prefs.clear();
    prefs.end();
    loadSettings();
  } else {
    Serial.println("Unknown command");
    printStatus();
    return;
  }
  saveSettings();
  startAdvertising();
  Serial.println("Saved.");
  printStatus();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // LED off: it's a bedroom device

  Serial.begin(115200);
  loadSettings();
  NimBLEDevice::init("Lodestone Night");
  startAdvertising();
  printStatus();
}

void loop() {
  static String line;
  while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n' || c == '\r') {
      handleCommand(line);
      line = "";
    } else if (line.length() < 80) {
      line += c;
    }
  }
  delay(20);
}
