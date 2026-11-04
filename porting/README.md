# Selected bare-metal porting artifacts

These files are **historical excerpts from an in-progress engineering port**, not a standalone MESA distribution or production-ready driver package.

| File | Engineering purpose |
|---|---|
| [`vtss_os_custom.h`](vtss_os_custom.h) | MESA OS abstraction: integer types, timing, platform allocation, timers, utility/compiler hooks. Derived from the Microchip-provided OS customization skeleton. |
| [`samv71-toolchain.cmake`](samv71-toolchain.cmake) | `arm-none-eabi` cross-compilation for Cortex-M7, Thumb, `softfp` ABI and FPU flags. |
| [`configure.sh`](configure.sh) | Selects custom OS, disables Linux/demo/shared builds, requests the LAN969x lightweight static target. |
| [`compile.sh`](compile.sh) | Builds `lan969x_lm_static`. |
| [`cmake-custom-os.patch`](cmake-custom-os.patch) | Focused diff against the upstream CMake build to add `MESA_OS_CUSTOM`, pass `VTSS_OS_CUSTOM`, and configure the 24-port lightweight target. |
| [`cortex-m-compat.patch`](cortex-m-compat.patch) | Avoids use of an incompatible ARM utility assembly path on Cortex-M, choosing the portable fallback. |

## Boundaries and limitations

- **This folder is not independently buildable.** The scripts require the appropriate full upstream MESA tree and the SAMV71 application/platform hooks, which are not distributed here.
- The OS header contains **declarations** of `mesa_malloc`, `mesa_free`, `delay_ms`, `delay_us`, and `get_global_ms`. Their application-level implementations are not in this repository.
- `VTSS_OS_CPU_TO_DMA_ADDR` is a **placeholder** in the archived header, not a verified DMA translation implementation. Its presence should not be interpreted as complete support for DMA-dependent functionality.
- Source selections are from an iterative development snapshot. Building/linking the trimmed library does **not** establish successful LAN9693 switch configuration or packet forwarding. Runtime execution reached `mesa_port_map_set()` before an unresolved hang.
- Vendor-origin source remains under the Microchip MIT terms indicated by its SPDX headers and [upstream notice](../LICENSES/upstream-notices.txt). Distribution of project-specific modifications should be reviewed against applicable employer disclosure requirements.

## Upstream context

Snapshot base: `microchip-ung/mesa` at commit `b7fbf512b279ebd557c081a47ec60b4c008410f8`.

Patches show differences in vendor files rather than reproducing entire original files. This is an engineering case study, **not** a fork supported by Microchip.
