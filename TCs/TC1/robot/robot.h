#ifndef _castle_h_
#define _castle_h_

#include "utils.h"
#include <GL/glu.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define CUBE_SIZE 0.5f

// Robot parts
#define HEAD 0
#define BODY 1
#define LEFT_ELBOW 2
#define RIGHT_ELBOW 3
#define LEFT_ARM 4
#define RIGHT_ARM 5
#define LEFT_KNEE 6
#define RIGHT_KNEE 7
#define LEFT_LEG 8
#define RIGHT_LEG 9

typedef struct Part {
	Rotation rotation;
	GLUquadricObj* part;
} Part;

typedef struct Robot {
	int numOfParts;
	float height;
	Part* parts;
} Robot;

// Define the camera position and orientation
static GLfloat cameraPosition[3] = {0.0f, 1.6f, 5.0f};
static GLfloat cameraDirection[3] = {0.0f, 0.0f, -1.0f};
static GLfloat cameraUp[3] = {0.0f, 1.0f, 0.0f};
static GLfloat cameraSpeed = 0.2f;
static GLfloat zoom = -9.0f;

const int colorPalette[] = { 	
	// Foundation Pieces
	0x5A5A5A,
	// Wires
	0x000000,
	// Beams
	0x303030,
	// Grass
	0x135000,
	// Robot
	0x334d5c
};

const double factoryHeight = 20.0f;
const double factoryBase = 1.0f;

static Rotation rotation;
static Coordinate position;
static Coordinate scale;

static Cylinder cylinder;
static Disk disk;
static Sphere sphere;

// Rotation
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int, int);
void SetupRC();
void SpecialKeys(int, int, int);
void RenderScene(void);

void drawFactory(GLfloat base, GLfloat height);
void drawCable(GLUquadricObj* quadObj, float base, float yPosition, float rightShift, float forwardShift);
void drawRobot(Coordinate position, float height);

Robot initRobot(int numOfParts, float height);

int main(int, char*[]);

#endif
