#!/bin/bash

# Change to the directory of the current script
cd "$(dirname "$0")"

# Clean previous build
cd ../src
make -f Makefile2 clean

# Build
make -f Makefile2

# Run if build was successful
if [ $? -eq 0 ]; then
    cd bin
    ./simulate_test1
else
    echo "Build failed"
fi