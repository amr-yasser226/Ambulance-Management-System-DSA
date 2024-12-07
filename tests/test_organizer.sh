#!/bin/bash

# Change to the directory of the current script
cd "$(dirname "$0")"

# Clean previous build
cd ../src
make -f organizer-Makefile clean

# Build
make -f organizer-Makefile

# Run if build was successful
if [ $? -eq 0 ]; then
    cd bin
    ./test_organizer
else
    echo "Build failed"
fi