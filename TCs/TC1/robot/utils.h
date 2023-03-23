#ifndef _utils_h_
#define _utils_h_

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265359

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

typedef struct Coordinate {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Coordinate;

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

bool isPointInsideOfCircle(float, Coordinate);

int randomNum(int, int);

void colorRgb(int);
void drawCube(int color, double size, Rotation rotation, Coordinate position, Coordinate scale);
void drawCylinder(int color, Cylinder cylinder, Rotation rotation, Coordinate position);
void drawDisk(int color, Disk disk, Rotation rotation, Coordinate position);
void drawSphere(int, Sphere sphere, Coordinate position);

void rotate(Rotation rotation);

Cylinder newCylinder(GLUquadric*, GLdouble, GLdouble, GLdouble, GLint, GLint);
Disk newDisk(GLUquadric*, GLdouble, GLdouble, GLint, GLint);
Sphere newSphere(GLUquadric*, GLdouble, GLint, GLint);
Coordinate newCoordinate(GLfloat x, GLfloat y, GLfloat z);
Rotation newRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif
