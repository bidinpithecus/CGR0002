# Vars
# The name of the final executable
LINKTARGET = main

# Compiler and linker settings
CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lGL -lglut -lGLU -ldl

# List of object files to build
OBJECTS = src/main.o \
          src/CApp.o \
          src/glad.o \
          src/particle/Color.o \
          src/particle/Firework.o \
          src/particle/Particle.o \
          src/particle/Random.o

# List of files to clean
BINARYS = main \
          *.out \

# List of files that can be rebuilt
REBUILDABLES = $(OBJECTS) $(LINKTARGET)

# Rules
# Rule for building the final executable
$(LINKTARGET): $(OBJECTS)
	$(CC) -g -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

# Rule for compiling object files from source code
src/%.o: src/%.cpp src/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling glad.c into an object file
src/glad.o: src/glad.c include/glad.h
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling particle source files into object files
src/particle/%.o: src/particle/%.cpp src/particle/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# Phony rule for cleaning build artifacts
.PHONY: clean
clean:
	@rm -i $(REBUILDABLES) $(BINARYS)
