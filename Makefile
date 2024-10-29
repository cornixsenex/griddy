CC = gcc
CFLAGS = -Wall -Werror -Iinclude
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image
SRC_DIR = src
INCLUDE_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

EXEC = griddy_sdl

all: $(EXEC)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(SDL_LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)
