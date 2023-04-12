#include "utils.h"

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

void drawSphere(int color, Sphere sphere, Position position) {
	Rgb color3f = hexTo3f(color);

	// save transform matrix state
	glPushMatrix();
	// setting the color that goes [0, 1]
	glColor3f(color3f.red, color3f.green, color3f.blue);
	// setting position in screen
	glTranslatef(position.x, position.y, position.z);
	// setting the sphere itself
	gluSphere(sphere.quad, sphere.radius, sphere.slices, sphere.stacks);
	// restore transform matrix state
	glPopMatrix();
}

double generateAnotherCoordinateOnSurface(double r, double y0, double c1, double c2, int xyz) {
	if (xyz == X) {
		return sqrt(pow(r, 2) - pow(c1, 2) + (2 * c1 * y0) - pow(y0, 2) - pow(c2, 2));
	} else if (xyz == Y) {
		return sqrt(pow(r, 2) - pow(c1, 2) - pow(c2, 2)) + y0;
		// return y0 - sqrt(pow(r, 2) - pow(c1, 2) - pow(c2, 2));
	} else if (xyz == Z) {
		return sqrt(pow(r, 2) - pow(c1, 2) - pow(c2 - y0, 2));
	} else {
		return 0;
	}
}

GLfloat generateCoordinateInsideSphere(GLfloat r, double y0, GLfloat c1, GLfloat c2) {
	float max = generateAnotherCoordinateOnSurface(r, c1, c2, y0, Y);

	return randomFloat(-max, max);
}

/*
	r stands for radius and x the sphere,
	y stands for the y position
*/
float calculateYAxisOfIntersection(float r0, float r1, float y0, float y1) {
	return ((y0 + y1) / 2.0) + ((pow(r0, 2) - pow(r1, 2)) / (2 * (y1 - y0)));
}

float calculateXAxisOfIntersection(float r, float y, float y0) {
	return sqrt(pow(r, 2) - pow(y - y0, 2));
}

int randomNum(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
    // Generate a random float between 0 and 1
    double randomDouble = (double)rand() / RAND_MAX;

    // Scale the random double to the desired range between min and max
    return min + randomDouble * (max - min);
}


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

Rotation newRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	Rotation rotation;
	rotation.angle = angle;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;

	return rotation;
}

Position newPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position position;
	position.x = x;
	position.y = y;
	position.z = z;

	return position;
}
