#!/usr/bin/env bash

set -e

cmake \
    -S . \
    -B build-samv71 \
    -DCMAKE_TOOLCHAIN_FILE="${PWD}/samv71-toolchain.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_MESA_ALL=OFF \
    -DBUILD_MESA_DEMO=OFF \
    -DMESA_OPSYS_LINUX=OFF \
    -DMESA_OPSYS_VELOCITYSP=OFF \
    -DMESA_OS_CUSTOM=ON \
    -DMESA_WRAP=ON \
    -DMESA_PRE_AG=ON \
    -DMESA_USE_INLINE_UTILS=ON \
    -Dlan969x_lm_static=ON \
    -Dlan969x_static=OFF 
