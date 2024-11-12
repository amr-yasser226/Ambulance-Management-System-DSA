# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -mconsole

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/test_patient

# Source files with corrected paths
PATIENT_SRC = $(SRC_DIR)/Patient/patient.cpp
TEST_SRC = ../tests/test_patient.cpp  # Adjusted path to go up one level and into tests
SRC_FILES = $(PATIENT_SRC) $(TEST_SRC)

# Object files with full paths
OBJ_FILES = $(OBJ_DIR)/patient.o $(OBJ_DIR)/test_patient.o

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

# Rule to compile patient.cpp to patient.o
$(OBJ_DIR)/patient.o: $(PATIENT_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile test_patient.cpp to test_patient.o
$(OBJ_DIR)/test_patient.o: $(TEST_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -rf $(BIN_DIR) $(OBJ_DIR)
