#!/bin/bash

set -e

PREMAKE_PATH="./vendor/bin/premake/Linux/premake5"

chmod +x $PREMAKE_PATH

echo "========== Generating Project Files =========="
$PREMAKE_PATH gmake2

echo ""
echo "========== Compiling Project (Debug) =========="
make config=debug -j$(nproc)

echo ""
echo "========== Build Completed Successfully! =========="
