# Compiler options
CC=gcc
CFLAGS=`sdl-config --cflags` -c -Wall
LDFLAGS=`sdl-config --libs` -l SDL_ttf -l SDL_image
EXECUTABLE_NAME=main

# Folders
SRC=src
BUILD=build
OBJ=$(BUILD)/obj

# Files
SOURCE_FILES=\
    main.c\
	tile.c\
	entity.c\
	board.c\
	game.c\
	utils.c\
	ui/component.c

# Compilation
EXECUTABLE_FILES = $(BUILD)/$(EXECUTABLE_NAME)
OBJECT_FILES     = $(SOURCE_FILES:%.c=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BUILD)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.c
	@echo Compiling $<
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<
