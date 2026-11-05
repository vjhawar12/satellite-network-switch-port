# Satellite Ethernet Switch: Linux-to-Bare-Metal Port and 95% MESA State RAM Reduction

**Engineering case study — SAMV71 Cortex-M7 · Microchip MESA SDK · LAN9693 Ethernet switch**

I led the bare-metal adaptation of a Linux-oriented MESA Ethernet-switch software stack for a SAMV71-controlled satellite-related system. I configured ARM cross-compilation and build integration, implemented the selected OS abstraction boundary, compiled and linked MESA into MCU firmware, and instrumented SDK allocations to profile and reduce memory requirements.

> **Key result:** Reduced the main MESA state object's *runtime heap allocation request* from **3,870,304 B** to **193,376 B** (about **95%**). This is not a claim that overall SRAM consumption or binary size fell by 95%.

**Engineering outcome:** Although the selected library built and linked and execution reached the port-configuration path, bring-up was not completed; `mesa_port_map_set()` later hung with a frozen CLI. The ~193 KB state allocation plus ~100 KB of separate static MESA data left limited space in the 384 KiB SRAM budget. Senior engineers subsequently investigated Linux-board alternatives. The hang's root cause was not established.

## Portfolio and evidence

- **[Four-page engineering portfolio (PDF)](portfolio/satellite-mesa-baremetal.pdf)** — system context, implementation ownership, profiling methodology, measured results and architectural tradeoff.
- **[Bare-metal porting artifacts](porting/)** — custom OS header, ARM cross-compilation toolchain, CMake patches and build commands.
- **[Runtime allocation notes](memory-optimization/rough_notes.txt)** — A cleaned-up version of the actual rough notes I made while memory profiling through eight successive stages and final 193,376 B request.
- **[Memory analysis and configuration diff](memory-optimization/optimization-changes.md)** — explains capacity reductions and why the full system remained constrained.

## My contributions

1. **Linux-independent MESA build and port** — customized platform headers for OS allocation and timing interfaces; added CMake custom-OS selection and the Cortex-M7 cross-toolchain; compiled a lightweight LAN969x static library and linked it against SAMV71 firmware.
2. **Runtime profiling** — used diagnostic statements around `vtss_state_t` and `mesa_malloc()` to identify large persistent allocations and break down sub-state/table usage.
3. **Configuration-driven RAM reduction** — progressively reduced VLAN, MAC, and port capacities, selected lightweight mode and trimmed optional capabilities, remeasuring after each iteration.
4. **Debugging and engineering assessment** — traced a runtime hang in `mesa_port_map_set()` and supplied memory measurements for assessing the feasibility of the microcontroller architecture.

## Important technical boundaries

- **Not a complete standalone firmware or MESA SDK fork.** The SAMV71 application, hardware design and board schematics are not published here.
- **Not a functional-switch demonstration.** Building/linking and reaching configuration code do not prove successful register configuration, switch bring-up or Ethernet forwarding.
- **Memory figures have distinct meanings.** The ~193 KB is one persistent runtime heap allocation; ~100 KB of additional static/global MESA data is an approximate separate SRAM demand. [See analysis.](memory-optimization/optimization-changes.md)
- **Historical code sample.** The archived custom OS header includes an unimplemented DMA conversion hook; it is not presented as a production-ready driver.
- **Provenance.** Upstream MESA code and headers originate with Microchip. Vendor-file changes are represented as focused patches; see [`LICENSES/upstream-notices.txt`](LICENSES/upstream-notices.txt). Company/customer details and proprietary board schematics are intentionally excluded. Public use of employer-related material is subject to authorization.

## File map

```text
portfolio/satellite-mesa-baremetal.pdf
porting/vtss_os_custom.h
porting/samv71-toolchain.cmake
porting/configure.sh
porting/compile.sh
porting/cmake-custom-os.patch
porting/cortex-m-compat.patch
porting/README.md
memory-optimization/rough_notes.txt
memory-optimization/optimization-changes.md
memory-optimization/configuration-changes.patch
LICENSES/upstream-notices.txt
```

The `rough_notes.txt` log is intentionally preserved as originally written in this repository; it was moved to a descriptive folder only.
