# Makefile for C++ project with main.cpp in the "main" directory

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source directory
SRC_DIR = main

# Build directory for object files
OBJ_DIR = obj

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Executable name
TARGET = bin/myprogram

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation step
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) bin)

# Clean
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)
