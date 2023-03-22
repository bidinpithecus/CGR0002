CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lGL -lglut -lGLU -lm
OBJECTS = snowman.o utils.o
BINARYS = snowman utils *.out

snowman: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINARYS) $(OBJECTS)
