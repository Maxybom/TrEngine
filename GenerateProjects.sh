#!/bin/bash

echo "=== CLEAN START ==="

echo "Searching and removing ALL bin and bin-int folders..."
find . -type d -name "bin" -exec rm -rf {} +
find . -type d -name "bin-int" -exec rm -rf {} +

echo "Searching and removing ALL old Makefiles..."
find . -type f -name "Makefile" -exec rm -f {} +
find . -type f -name "*.make" -exec rm -f {} +

echo "=== CLEAN COMPLETE ==="
echo "=== PREMAKE EXECUTION ==="

./premake5 gmake2

echo ""
echo "Done"
echo "Press ENTER to close..."
read
