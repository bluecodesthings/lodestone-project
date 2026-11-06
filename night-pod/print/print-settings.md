# Print settings

Starting points for an FDM printer with a 0.4 mm nozzle.

| Setting | Value |
|---|---|
| Material | PLA. Dark navy matches the renders. |
| Layer height | 0.2 mm |
| Walls | 4 |
| Top/bottom layers | 6 |
| Infill | 100% (extra weight) or 20% to save time |
| Supports | None |

## Orientation
- **pod-top:** flip it upside down so the flat top with the moon is on the bed. The board cradle, pins and bosses then print straight up. The files in `mcgill-submission/` are already flipped.
- **pod-base:** flat bottom on the bed, as exported.

## Print time (estimate)
Sliced with PrusaSlicer using Ultimaker S5-style PLA settings (0.2 mm, 4 walls, 100% infill):

| Part | Time | Filament |
|---|---|---|
| pod-top | ~3 h 56 min | ~43 g |
| pod-base | ~1 h 58 min | ~27 g |
| **Both** | **~5 h 55 min** | **~70 g** |

## Fit checks
Print a test of the board cradle area before the full top if you're unsure of your board's size. Measure your SuperMini with calipers and update `pcb_l`, `pcb_w` and `pcb_t` in the CAD file if they differ from 22.5 × 18 × 1.0 mm.
