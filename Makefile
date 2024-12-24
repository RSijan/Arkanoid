# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++17 \
           -Wextra -Wpedantic \
           -Wconversion -Wsign-conversion \
           -Wfloat-equal -Wshadow -Wuninitialized \
           -Wunused-parameter -Wmissing-declarations -Wmissing-include-dirs \
           -Wnoexcept -Wnon-virtual-dtor -Weffc++
		   -fsanitize=address -fsanitize=undefined


# Include directories
INC_DIR = -Isrc

# Source directories
SRC_DIR = src

# Object file directory
OBJ_DIR = obj

# Source files (list your .cpp files here)
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Executable name
TARGET = arkanoid

# Libraries for allegro
LIBS = -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_main

# Linker flags (add allegro libraries here)
LDFLAGS = $(LIBS)

# Object directory
OBJECT_DIR := $(OBJ_DIR)

# Default target
all: $(TARGET)

# Compile .cpp files into .o files
$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling: $< into $@"
	@mkdir -p $(OBJECT_DIR)/$(dir $(patsubst $(SRC_DIR)/%,%,$<))
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC_DIR)


# Link object files into the final executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS)  $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

run:
	./$(TARGET)