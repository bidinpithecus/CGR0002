#ifndef _utils_h_
#define _utils_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

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

typedef struct Position {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Position;

typedef struct Rgb {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
} Rgb;

typedef struct Rotation {
	GLfloat angle;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Rotation;

typedef struct Sphere {
	GLUquadric* quad;
	GLdouble radius;
	GLint slices;
	GLint stacks;
} Sphere;

Rgb hexTo3f(int);

GLfloat getZOnSurface(GLfloat radius, GLfloat x, GLfloat y);

int randomNum(int min, int max);

void drawCylinder(int, Cylinder, Rotation, Position);
void drawDisk(int, Disk, Rotation, Position);
void drawSphere(int, Sphere, Position);

Cylinder newCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
Disk newDisk(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops);
Sphere newSphere(GLUquadric*, GLdouble, GLint, GLint);
Position newPosition(GLfloat x, GLfloat y, GLfloat z);
Rotation newRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif
