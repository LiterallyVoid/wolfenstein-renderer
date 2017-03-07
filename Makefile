CFLAGS = `pkg-config --cflags sdl` -Ofast -g
LDFLAGS = `pkg-config --static --libs sdl` -g -lSDL_gfx

OBJS = src/main.o

currentproject: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)