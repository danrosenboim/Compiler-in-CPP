# Compiler settings
CXX = g++
CXXFLAGS = -g -Wall -Wextra

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files - flattening directory structure
SOURCES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = compiler

# Function names
.PHONY: all clean directories

all: directories $(TARGET)

# Linking files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

# Converting files to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


directories:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
