# Output file
TARGET = build/main.exe

# Compiler and Flags
CC = g++
CFLAGS = -Wall -g -std=c++20

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

# FFmpeg settings
FFMPEG_FLAGS = $(shell pkg-config --cflags --libs libavformat libavcodec libswresample libavutil libswscale)
CFLAGS += $(FFMPEG_FLAGS)
LDLIBS += $(shell pkg-config --libs libavformat libavcodec libswscale libswresample libavutil)

# SDL2 settings
SDL2_FLAGS = $(shell pkg-config --cflags --libs sdl2 SDL2_mixer)
CFLAGS += $(SDL2_FLAGS)
LDLIBS += $(shell pkg-config --libs sdl2 SDL2_mixer)

# FTXUI settings
FTXUI_FLAGS = -I./FTXUI/include
FTXUI_LIBS = ./FTXUI/build/libftxui-component.a ./FTXUI/build/libftxui-dom.a ./FTXUI/build/libftxui-screen.a
CFLAGS += $(FTXUI_FLAGS)
LDLIBS += $(FTXUI_LIBS) -pthread -lncurses

# TagLib settings
CFLAGS += -I/usr/include/taglib
LDFLAGS += -L/usr/lib/x86_64-linux-gnu
LDLIBS += -ltag

# ICU settings
ICU_FLAGS = -licuuc -licudata -licui18n
LDLIBS += $(ICU_FLAGS)

# Main rule
all: $(TARGET)

# Create executable file
$(TARGET): $(OBJS)
	@mkdir -p $(@D)
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
