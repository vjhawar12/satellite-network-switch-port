# MESA runtime state allocation — engineering explanation

The detailed measurement record is preserved **unchanged** in [`rough_notes.txt`](rough_notes.txt). This page connects the trace numbers to the code changes and the actual system decision.

## What was instrumented

The MESA instance-creation path allocates a state object derived from `sizeof(vtss_state_t)` using `mesa_malloc()`. Debug statements recorded the state size, allocation request and selected component/table sizes between iterative builds. The captured allocation requests include allocator alignment and must not be confused with flash footprint, the static library size, or all SRAM used by the firmware.

- Recorded baseline request: **3,870,304 B**.
- Last recorded request: **193,376 B** (`sizeof(vtss_state_t) = 193,360 B`).
- Reduction: **3,676,928 B, approximately 95.0%** for this single persistent runtime state allocation.

## Main trimming mechanisms

| Mechanism | Relevant source | Why it affects runtime allocation |
|---|---|---|
| VLAN capacity 4,096 → 64 | `include/vtss/api/types.h` | Shrinks fixed-size arrays embedded in MESA state structures, including `vlan_table[VTSS_VIDS]`. |
| MAC capacity 16,384 → 128 | Selected lightweight configuration and state definitions | Shrinks `mac_table[VTSS_MAC_ADDRS]` and related pointer state. |
| Port capacity 30 → 24 | CMake `-DVTSS_OPT_PORT_COUNT=24` and matching integration configuration | Shrinks per-port arrays across multiple state components. |
| Lightweight MESA target | `lan969x_lm_static`, `-DVTSS_OPT_LIGHT=1` | Removes or reduces features and their compile-time state. |
| Feature/capacity trimming | [`configuration-changes.patch`](configuration-changes.patch) | Disables TAS feature declarations and reduces configured L3 limits in the archived snapshot. |

The source snapshot supplied here does **not** reproduce the entire final ~193 KB configuration: the notes record later L3/VCAP reductions, but do not identify all exact source flags responsible for that final step. It would be misleading to claim the listed patch alone rebuilds the final result.

## Total RAM feasibility

The SAMV71 configuration had **384 KiB of SRAM**. The final MESA state allocation was ~193 KB, alongside approximately **100 KB of separate MESA static/global `.bss`/`.data` arrays**, before the rest of the application and stacks. These are separate consumers, not simply the same heap reserved in `.bss`. Together they accounted for roughly **three-quarters of available SRAM**, with limited remaining headroom.

The archived notes use a **256 KiB heap pool** for the allocator context; earlier, different profiling configurations existed. Pool size is not the total physical MCU SRAM. The MESA instance's reduction did not establish system viability.

## Outcome

The trimmed MESA library was cross-compiled and linked into the SAMV71 firmware. Execution reached `mesa_port_map_set()`, where the debugger stopped progressing and the CLI froze; no root cause was conclusively established. Senior engineers then began evaluating Linux-based platforms instead of continuing the tightly constrained MCU integration. This was a team architecture decision informed by memory feasibility, **not** proof that RAM exhaustion caused the port-mapping hang.
