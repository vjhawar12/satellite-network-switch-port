#!/usr/bin/env bash 
set -e 

cmake --build build-samv71 --target lan969x_lm_static --parallel
