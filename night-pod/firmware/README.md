# Lodestone beacon firmware

Turns an ESP32-C3 SuperMini into an iBeacon for the Night Pod. Settings are stored on the board and can be changed over USB, so you only flash it once.

| Default | Value |
|---|---|
| UUID | `A4BA2C0E-C9E0-4EFD-ACDC-0A8E782A5F81` (shared by all Lodestone pods) |
| Major / minor | 1 / 1. Give each pod a different minor if you have several. |
| Transmit power | -12 dBm (about one room; tune below) |
| Measured power | -70 dBm at 1 m |
| Interval | 300 ms |
| LED | off |

## Flashing
**Arduino IDE:**
1. Install the **esp32 by Espressif** boards package (3.x).
2. Install the **NimBLE-Arduino** library (2.x).
3. Open `lodestone-beacon/lodestone-beacon.ino`.
4. Choose board **ESP32C3 Dev Module** and set **USB CDC On Boot: Enabled**.
5. Upload.

**Command line:**
```sh
arduino-cli core install esp32:esp32
arduino-cli lib install NimBLE-Arduino
arduino-cli compile --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc lodestone-beacon
arduino-cli upload  --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc -p /dev/cu.usbmodem* lodestone-beacon
```
If the upload doesn't start, hold **BOOT**, tap **RESET**, release **BOOT**, then try again.

## Settings over USB
Open a serial monitor at 115200 baud (Arduino IDE → Serial Monitor, or `arduino-cli monitor -p /dev/cu.usbmodem* -c baudrate=115200`) and type:

| Command | Effect |
|---|---|
| `status` | Show the current settings |
| `tx -12` | Transmit power in dBm (-24 to 20). Lower means a smaller zone. |
| `mp -70` | Measured power: the RSSI your phone sees at 1 m |
| `major 1`, `minor 2` | Pod IDs |
| `uuid <uuid>` | Use your own UUID |
| `reset` | Back to the defaults |

Every change is saved and applied immediately.

## Calibrating the range
1. Install **nRF Connect** (iOS) or any BLE scanner, and find the "Lodestone Night" iBeacon.
2. Stand where you want the zone to end (e.g. your bedroom door) and watch the RSSI.
3. Lower `tx` in steps of 3 dB until the beacon is weak or missing at the door, but still strong at your bed.
4. Set `mp` to the RSSI you read 1 m from the pod.

Walls, your body and the phone's case all change the signal. Treat the zone as a bubble around the pod, not an exact room outline.
