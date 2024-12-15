#!/bin/bash

# Change to the directory of the current script
cd "$(dirname "$0")"

# Clean previous build
cd ../src
make -f ui-Makefile clean

# Build
make -f ui-Makefile

# Run if build was successful
if [ $? -eq 0 ]; then
    cd bin
    ./test_ui
else
    echo "Build failed"
fi