#ifndef _snowman_h_
#define _snowman_h_

#include "app.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define RIGHT 1
#define LEFT -1

// Define the camera movement speed
extern int color;

extern Cylinder cylinder;
extern Disk disk;
extern Sphere sphere;

extern Position position;
extern Rotation rotation;

void drawArm(double bodyRadius, double bodyY, GLUquadricObj* pObj, int side);

#endif
