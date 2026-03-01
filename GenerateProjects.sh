#!/bin/bash

echo "=== CLEAN START ==="

find . -type d -name "bin" -not -path "./vendor/*" -exec rm -rf {} +
find . -type d -name "bin-int" -not -path "./vendor/*" -exec rm -rf {} +

find . -type f -name "Makefile" -exec rm -f {} +
find . -type f -name "*.make" -exec rm -f {} +

echo "=== CLEAN COMPLETE ==="
echo "=== PREMAKE EXECUTION ==="

chmod +x vendor/bin/premake/Linux/premake5

./vendor/bin/premake/Linux/premake5 gmake2
