#ifndef _utils_h_
#define _utils_h_

#include <GL/gl.h>
#include <GL/glut.h>

typedef struct Rgb {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
} Rgb;

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

typedef struct Sphere {
    GLUquadric* quad;
    GLdouble radius;
    GLint slices;
	GLint stacks;
} Sphere;

typedef struct Position {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Position;

typedef struct Rotation {
    GLfloat angle;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Rotation;

Rgb hexTo3f(int);

Cylinder newCylinder(GLUquadric*, GLdouble, GLdouble, GLdouble, GLint, GLint);
Disk newDisk(GLUquadric*, GLdouble, GLdouble, GLint, GLint);
Sphere newSphere(GLUquadric*, GLdouble, GLint, GLint);
Position newPosition(GLfloat, GLfloat, GLfloat);
Rotation newRotation(GLfloat, GLfloat, GLfloat, GLfloat);

void drawSphere(int, Sphere, Position);
void drawDisk(int, Disk, Rotation, Position);
void drawCylinder(int, Cylinder, Rotation, Position);

#endif
