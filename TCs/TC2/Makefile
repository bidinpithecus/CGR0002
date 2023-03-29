# Vars
LINKTARGET = main

CC = g++

CFLAGS = -Wall -Wextra -std=c++17

LDFLAGS = -lGL -lglut -lGLU -lSDL2 -lm

OBJECTS = main.o \
			CApp.o \
			$(patsubst %.cpp, %.o,$(wildcard ./particle/*.cpp))

BINARYS = *.out *.o

REBUILDABLES = $(OBJECTS) $(LINKTARGET)

# Rules
$(LINKTARGET): $(OBJECTS)
	@$(CC) -g -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONEY:
clean:
	@rm -f $(REBUILDABLES)
