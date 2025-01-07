# Output file
TARGET = build/main.exe

# Compiler and Flag
CC = g++
CFLAGS = -Wall -g

# Source folder, header folder
SRCDIR = Src
INCDIR = Include

# Automatically find all subdirectories in Include and Src
INCLUDES = $(shell find $(INCDIR) -type d)
CFLAGS += $(foreach dir, $(INCLUDES), -I$(dir))

# Find all .cpp files in Src (do not include main.cpp multiple times)
SRCS = $(shell find $(SRCDIR) -name "*.cpp")

# Main rule
all: $(TARGET)

# Create executable file without .o files
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule (no need to clean .o files)
clean:
	rm -f $(TARGET)

# Run executable
run: all
	./$(TARGET)
