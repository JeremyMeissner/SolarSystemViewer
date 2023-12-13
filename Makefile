# The compiler
CC:=gcc
# The flags passed to the compiler
CFLAGS:=-g -Ofast -Wall -Wextra -fsanitize=address -I/opt/homebrew/include
# The flags passed to the linker
# Add the SDL2 library path with -L/opt/homebrew/lib
LDFLAGS:=-lm -L/opt/homebrew/lib -lSDL2
# Path to the lib Vec2
VPATH:=vec2 gfx planet

main: main.o vec2.o gfx.o planet.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run_tests: tests
	./$<

tests: vec_tests.o vec2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

planet.o: planet.h

vec2.o: vec2.h

gfx.o: gfx.h

clean:
	rm -f *.o main tests
