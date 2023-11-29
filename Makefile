CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR := src
TESTS_DIR := tests
OBJ_DIR := obj
BIN_DIR := bin

# Find all source files in the source directory
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(SRC_DIR)/QR.cpp

# Create a list of object files based on the source files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Test source files
TEST_SRC_FILES := $(wildcard $(TESTS_DIR)/*.cpp)

# Test executable names
TEST_BINS := $(patsubst $(TESTS_DIR)/%.cpp,$(BIN_DIR)/%,$(TEST_SRC_FILES))

# Default target
all: $(OBJ_FILES)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build test executables
$(BIN_DIR)/%: $(TESTS_DIR)/%.cpp $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Target to build and run tests without profiling
test: $(TEST_BINS)
	@echo "Running tests..."
	@$(foreach test, $(TEST_BINS), ./$(test);)

# Target to build and run tests with profiling
profile: CXXFLAGS += -pg
profile: test
	@gprof $(BIN_DIR)/QRTest > profile_output.txt

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all test profile clean



# make test
# make test profile
# make clean