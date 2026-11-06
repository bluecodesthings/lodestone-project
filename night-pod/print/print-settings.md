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
- **pod-top:** lay the sloped top (with the moon) flat on the bed. In a slicer use "Place on face" and pick the sloped top, which is a 168° rotation around X. The inside features then print leaning 12°, which needs no supports. The file in `mcgill-submission/` is already rotated.
- **pod-base:** flat bottom on the bed, as exported.

## Print time (estimate)
Sliced with PrusaSlicer using Ultimaker S5-style PLA settings (0.2 mm, 4 walls, 100% infill):

| Part | Time | Filament |
|---|---|---|
| pod-top | ~3 h 39 min | ~40 g |
| pod-base | ~1 h 41 min | ~25 g |
| **Both** | **~5 h 20 min** | **~65 g** |

## Fit checks
Print a test of the board cradle area before the full top if you're unsure of your board's size. Measure your SuperMini with calipers and update `pcb_l`, `pcb_w` and `pcb_t` in the CAD file if they differ from 22.5 × 18 × 1.0 mm.
