# Assembly

## 1. Flash the board first
Follow the [firmware README](../firmware/README.md) and check that a BLE scanner sees the beacon before you build it in.

## 2. Steel
Cut one or two 50 mm pieces from the 1½″ × ¼″ bar, deburr them and drop them into the tray at the **front** of the base (long side left-to-right). The default print is sized for **two**. For one, set `st_n = 1` in the CAD file and re-export, or add a 6 mm foam pad on top of the single plate.

## 3. Heat-set inserts (top)
With the top upside down, press an M2 insert into each corner boss at about 220 °C (PLA) until it's flush.

## 4. Board
1. With the top still upside down, hold the ESP32-C3 with its **flat back toward the two support ribs** (components facing you), USB-C end toward the back.
2. Tilt the board and put its USB-C end against the two small back tabs (the port sits between them).
3. Press the front end down onto the ribs, past the small snap lip on the front wall. It clicks in behind the lip.

## 5. USB-C extension
1. Plug the extension's **male** end into the board's USB-C port.
2. Put a small square of foam tape under the extension's **socket** end and press it into the holder at the back of the base. The socket faces the opening in the back wall; the ribbon leaves between the two front posts.
3. Fold the spare ribbon loosely beside the board. Don't crease it sharply.

## 6. Close
Lower the base onto the top, guiding the ribbon so it isn't pinched. The ledge aligns it, and the 4 pins press on the steel. Drive 4 × M2 × 6 countersunk screws into the inserts.

## 7. Feet
Wipe the 4 pockets with alcohol, prime the silicone feet and glue them in with CA.

## 8. Set it up
Plug your USB-C cable into the socket at the bottom of the back. You can still change the beacon settings over USB through the extension.
Place it by the bed and calibrate the range (see the [firmware README](../firmware/README.md#calibrating-the-range)).

## Repair
Remove the 4 screws and lift off the top. The board stays in its cradle; push the front edge back over the lip to remove it.
