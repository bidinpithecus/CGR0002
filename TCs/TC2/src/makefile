CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lGL -lglut -lGLU -lm
OBJECTS = snowman.o utils.o app.o
BINARYS = snowman utils app

snowman: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINARYS) $(OBJECTS)
