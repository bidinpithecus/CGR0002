#ifndef _utils_h_
#define _utils_h_

#include <GL/glut.h>

typedef struct Rgb {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Rgb;

typedef struct Position {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Position;

typedef struct Sphere {
    GLUquadric* quad;
    GLdouble radius;
    GLint slices;
	GLint stacks;
} Sphere;

typedef struct Cylinder {
    GLUquadric* quad;
	GLdouble base;
	GLdouble top;
	GLdouble height;
	GLint slices;
	GLint stacks;
} Cylinder;

typedef struct Disk {
    GLUquadric* quad;
	GLdouble inner;
	GLdouble outer;
	GLint slices;
	GLint loops;
} Disk;

typedef struct Rotation {
    GLfloat angle;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Rotation;

Rgb hexTo3f(int);

void drawSphere(Rgb, Sphere, Position);
void drawDisk(Rgb, Disk, Rotation, Position);
void drawCylinder(Rgb, Cylinder, Position);

#endif
