#!/bin/bash

# Get the directory of the current script
SCRIPT_DIR="$(dirname "$0")"

# Detect OS
case "$(uname -s)" in
    Linux*)     
        echo "Running on Linux"
        # Linux build commands
        cd "$SCRIPT_DIR"/../src
        make -f ui-Makefile clean
        make -f ui-Makefile
        if [ $? -eq 0 ]; then
            cd bin
            ./test_ui
        else
            echo "Build failed"
        fi
        ;;
    MINGW*|MSYS*|CYGWIN*)     
        echo "Running on Windows"
        # Windows build commands
        cd "$SCRIPT_DIR"/../src
        mingw32-make -f ui-Makefile clean
        mingw32-make -f ui-Makefile
        if [ $? -eq 0 ]; then
            cd bin
            ./test_ui.exe
        else
            echo "Build failed"
        fi
        ;;
    *)          
        echo "Unknown operating system"
        exit 1
        ;;
esac