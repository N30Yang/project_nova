#!/bin/sh
set -e
cd "$(dirname "$0")"
mkdir -p build
CXX="${CXX:-g++}"
FLAGS="-std=c++17 -Wall -Wextra -Wno-unused-parameter -Istubs"
echo "=== default settings ==="
$CXX $FLAGS sim.cpp -o build/sim
./build/sim
echo
echo "=== stress: intensity 1.0, PLANET_CROUCH_WALK + PLANET_STORM_SWAY on ==="
sed -e 's/PLANET_INTENSITY       = [0-9.]*f/PLANET_INTENSITY       = 1.0f/' \
    -e 's/PLANET_CROUCH_WALK     = false/PLANET_CROUCH_WALK     = true/' \
    -e 's/PLANET_STORM_SWAY      = false/PLANET_STORM_SWAY      = true/' \
    ../../firmware/movement-sequences.h > build/movement-sequences-stress.h
$CXX $FLAGS -DPLANET_HEADER='"build/movement-sequences-stress.h"' sim.cpp -o build/sim-stress
./build/sim-stress