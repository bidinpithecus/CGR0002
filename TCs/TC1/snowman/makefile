CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LDFLAGS=-lGL -lglut -lGLU

snowman: snowman.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

snowman.o: snowman.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f snowman.o snowman

