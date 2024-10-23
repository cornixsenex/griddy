CC = gcc
CFLAGS = -Wall -Werror 
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

TARGET = griddy_sdl
SOURCE = test_sdl.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -o $@ $< $(SDL_LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
