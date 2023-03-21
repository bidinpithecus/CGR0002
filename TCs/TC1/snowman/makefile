CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lGL -lglut -lGLU
OBJECTS = snowman.o utils.o

snowman: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f snowman utils $(OBJECTS)
