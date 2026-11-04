# samv71_toolchain.cmake
#
# Cross-compilation toolchain for Microchip SAMV71
# using the GNU Arm Embedded toolchain.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Cross compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

# Prevent CMake from trying to build and run host executables
# during compiler detection.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# -------------------------------------------------------------------
# SAMV71 architecture flags
#
# IMPORTANT:
# These must match the existing Microchip Studio SAMV71 project.
# Do not guess the FPU/float ABI.
# -------------------------------------------------------------------

set(SAMV71_CPU_FLAGS
    -mcpu=cortex-m7
    -mthumb
    -mlong-calls
    -mfloat-abi=softfp
    -mfpu=fpv4-sp-d16
)

add_compile_options(
    ${SAMV71_CPU_FLAGS}
    -std=gnu11
    -ffunction-sections
)

# Apply the same architecture flags when linking if CMake ever performs
# a link step through this toolchain.
add_link_options(
    ${SAMV71_CPU_FLAGS}
)
