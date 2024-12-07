#!/bin/bash

# Navigate to the root directory of the project
cd "$(dirname "$0")"
cd ../src

# Run the make command to build the project
make -f car-Makefile

# Check if the executable was created successfully
if [ -f "bin/test_car" ]; then
    echo "Running tests..."
    ./bin/test_car
else
    echo "Build failed. Please check the errors above."
fi
