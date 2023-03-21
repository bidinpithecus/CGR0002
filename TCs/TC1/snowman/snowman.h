#ifndef _snowman_h_
#define _snowman_h_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "utils.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);

#endif
