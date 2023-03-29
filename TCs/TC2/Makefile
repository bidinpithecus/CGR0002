CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lGL -lglut -lGLU -lSDL2 -lm
OBJECTS = src/CApp.o src/main.o
BINARYS = *.out

main: $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(BINARYS) $(OBJECTS)
