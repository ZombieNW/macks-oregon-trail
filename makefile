# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXE := game.exe

# Default rule
all: $(EXE)

# Rule to build the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(EXE)

test:
	game.exe