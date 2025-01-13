# Output file
TARGET = build/main.exe

# Compiler and Flag
CC = g++
CFLAGS = -Wall -g

# Source folder, header folder
SRCDIR = src
INCDIR = include
OBJDIR = build/obj

# Automatically find all subdirectories in Include and Src
INCLUDES = $(shell find $(INCDIR) -type d)
CFLAGS += $(foreach dir, $(INCLUDES), -I$(dir))

# Find all .cpp files in Src (do not include main.cpp multiple times)
SRCS = $(shell find $(SRCDIR) -name "*.cpp")
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# TagLib settings (adjust these if TagLib is in a custom location)
CFLAGS += -I/usr/include/taglib        # Đường dẫn đến thư mục chứa header của TagLib
LDFLAGS += -L/usr/lib/x86_64-linux-gnu  # Đường dẫn đến thư mục chứa thư viện libtag.so
LDLIBS += -ltag                        # Liên kết với thư viện TagLib

# SDL2 settings
CFLAGS += -I/usr/include/SDL2           # Đường dẫn đến thư mục chứa header của SDL2
LDLIBS += -lSDL2 -lSDL2_mixer           # Liên kết với thư viện SDL2

# Main rule
all: $(TARGET)

# Create executable file
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Compile .cpp files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule (clean object files and executable)
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Run executable
run: all
	./$(TARGET)
