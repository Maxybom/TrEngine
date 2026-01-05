#!/bin/bash

echo "=== CLEAN START ==="

echo "Searching and removing bin and bin-int folders (skipping vendor)..."
find . -type d -name "bin" -not -path "./vendor/*" -exec rm -rf {} +
find . -type d -name "bin-int" -not -path "./vendor/*" -exec rm -rf {} +

echo "Searching and removing old Makefiles..."
find . -type f -name "Makefile" -exec rm -f {} +
find . -type f -name "*.make" -exec rm -f {} +

echo "=== CLEAN COMPLETE ==="
echo "=== PREMAKE EXECUTION ==="

# Pointing to the actual executable file inside the Linux folder
chmod +x vendor/bin/premake/Linux/premake5

./vendor/bin/premake/Linux/premake5 gmake2

echo ""
echo "Done"
echo "Press ENTER to close..."
read