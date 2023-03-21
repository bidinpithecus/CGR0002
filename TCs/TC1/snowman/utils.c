#include "utils.h"

Rgb hexTo3f(int hexValue) {
	Rgb rgb;
	rgb.red = ((hexValue >> 16) & 0xFF) / 255.0;
	rgb.green = ((hexValue >> 8) & 0xFF) / 255.0;
	rgb.blue = ((hexValue) & 0xFF) / 255.0;

	return rgb; 
}

Cylinder newCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {
	Cylinder cylinder;
	cylinder.quad = quad;
	cylinder.base = base;
	cylinder.top = top;
	cylinder.height = height;
	cylinder.slices = slices;
	cylinder.stacks = stacks;

	return cylinder;
}

Disk newDisk(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops) {
	Disk disk;
	disk.quad = quad;
	disk.inner = inner;
	disk.outer = outer;
	disk.slices = slices;
	disk.loops = loops;

	return disk;
}

Sphere newSphere(GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks) {
	Sphere sphere;
	sphere.quad = quad;
	sphere.radius = radius;
	sphere.slices = slices;
	sphere.stacks = stacks;

	return sphere;
}

Position newPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position position;
	position.x = x;
	position.y = y;
	position.z = z;

	return position;
}

Rotation newRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	Rotation rotation;
	rotation.angle = angle;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;

	return rotation;
}

void drawSphere(int color, Sphere sphere, Position position) {
	Rgb color3f = hexTo3f(color);
	
	// save transform matrix state
	glPushMatrix();
	// setting the color that goes [0, 1]
	glColor3f(color3f.red, color3f.green, color3f.blue);
	// setting position in screen
	glTranslatef(position.x, position.y, position.z);
	// setting the sphere itself
	gluSphere(sphere.quad, sphere.radius, sphere.radius, sphere.stacks);
	// restore transform matrix state
	glPopMatrix();
}

void drawDisk(int color, Disk disk, Rotation rotation, Position position) {
	Rgb color3f = hexTo3f(color);

	// save transform matrix state
	glPushMatrix();
	glColor3f(color3f.red, color3f.green, color3f.blue);
	// setting position in screen
	glTranslatef(position.x, position.y, position.z);
	// setting rotation in screen
	glRotatef(rotation.angle, rotation.x, rotation.y, rotation.z);
	// setting the disk itself
	gluDisk(disk.quad, disk.inner, disk.outer, disk.slices, disk.loops);
	// restore transform matrix state
	glPopMatrix();
}

void drawCylinder(int color, Cylinder cylinder, Rotation rotation, Position position) {
	Rgb color3f = hexTo3f(color);

	// save transform matrix state
	glPushMatrix();
	glColor3f(color3f.red, color3f.green, color3f.blue);
	// setting position in screen
	glTranslatef(position.x, position.y, position.z);
	// setting rotation in screen
	glRotatef(rotation.angle, rotation.x, rotation.y, rotation.z);
	// setting the disk itself
	gluCylinder(cylinder.quad, cylinder.base, cylinder.top, cylinder.height, cylinder.slices, cylinder.stacks);
	// restore transform matrix state
	glPopMatrix();
}
