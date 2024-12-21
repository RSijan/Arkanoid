# Compiler and flags
CC = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror \
           -Wpedantic -Wconversion -Wsign-conversion \
           -Wfloat-equal -Wshadow -Wuninitialized \
           -Wunused-parameter -Wmissing-declarations -Wmissing-include-dirs \
           -Wnoexcept -Wnon-virtual-dtor -Weffc++

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")

# Object files (matching source files)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable name
TARGET = arkanoid

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(shell dirname $@)  # Create intermediate object directory
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean