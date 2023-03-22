#ifndef _snowman_h_
#define _snowman_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "utils.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

// Rotation
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Camera
static GLfloat zoom = -5.0f;

// Define the camera position and orientation
extern GLfloat cameraDirection[3];
extern GLfloat cameraPosition[3];
extern GLfloat cameraUp[3];

// Define the camera movement speed
extern GLfloat cameraSpeed;

extern int color;

extern Cylinder cylinder;
extern Disk disk;
extern Sphere sphere;

extern Position position;
extern Rotation rotation;

void ChangeSize(int, int);
void keyboardCallback(unsigned char, int, int);
void RenderScene(void);
void SetupRC();
void SpecialKeys(int, int, int);
int main(int, char*[]);

#endif
