#!/bin/bash

set -e

echo "========== Generating Project Files =========="
./premake5 gmake2

echo ""
echo "========== Compiling Project (Debug) =========="
make config=debug -j$(nproc)

echo ""
echo "========== Build Completed Successfully! =========="
