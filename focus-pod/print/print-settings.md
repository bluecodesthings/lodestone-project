# Print settings

Tested values are still to come. These are starting points for any FDM printer with a 0.4 mm nozzle.

| Setting | Value |
|---|---|
| Material | PLA (PETG works too) |
| Layer height | 0.2 mm (0.12–0.16 mm for a nicer rounded edge) |
| Walls | 4 |
| Top/bottom layers | 6 |
| Infill | 100% (or 40% gyroid; the parts are mostly walls anyway) |
| Supports | None |
| Brim | Not needed |

## Orientation
- **pod-top:** **flip it upside down** so the flat top face is on the bed. In your slicer, use "Lay on face" and pick the top. The pins, bosses and tag ring then print straight up, and the visible top is smooth. The 0.4 mm symbol and corner marks print as recesses in the first 2 layers. To make them stand out, pause after layer 2 and swap filament colour, or fill them with acrylic paint and wipe off the excess.
- **pod-base:** print as exported, with the flat bottom (feet pockets) on the bed. The pockets bridge cleanly and the countersinks are 45° overhangs.

## Fit check
Print the base first. The steel should drop into the ledge window, and the top should slide over the ledge without forcing. If it's too tight, raise `clr` in the CAD file (try 0.25–0.3) and re-export.

## Print time (estimate)
Sliced with PrusaSlicer using Ultimaker S5-style PLA settings: 2.85 mm filament, 0.4 nozzle, 0.2 mm layers, Cura-like speeds.

| Part | Time | Filament |
|---|---|---|
| pod-top | ~1 h 02 min | ~9.8 g |
| pod-base | ~44 min | ~10.1 g |
| **Both** | **~1 h 45 min** | **~20 g** |

Infill barely matters because the parts are almost all walls. Cura's own estimate on an Ultimaker S5 or Ultimaker 3 may differ by about ±20%.
