#!/bin/bash

# Change to the directory of the current script
cd "$(dirname "$0")"

# Go up one directory 
cd ../src

# Run make with Makefile2
make -f Makefile2

# Change to bin directory
cd ../src/bin

# Run the simulation test
./simulate_test1