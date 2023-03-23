#ifndef _castle_h_
#define _castle_h_

#include "utils.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define CUBE_SIZE 0.5f

// Define the camera position and orientation
static GLfloat cameraPosition[3] = {0.0f, 0.0f, 5.0f};
static GLfloat cameraDirection[3] = {0.0f, 0.0f, -1.0f};
static GLfloat cameraUp[3] = {0.0f, 1.0f, 0.0f};
static GLfloat cameraSpeed = 0.2f;

const int colorPalette[] = { 	
	// Walls
	0x5A5A5A,
	// Roof
	0xDC5539,
	// Flag
	0x5E3C99,
	// Flag Haste
	0x000000,
	// Tree
	0x765C48,
	// Leaves
	0x2E8D36,
	// Mud
	0x261c06,
	// Grass
	0x135000,
	// Water
	0x010D14
};

const double factoryHeight = 20.0f;
const double factoryBase = 1.0f;

static Rotation rotation;
static Coordinate position;
static Coordinate coordinate;
static Coordinate scale;

static Cylinder cylinder;

// Rotation
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Camera
static GLfloat zoom = -5.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int, int);
void SetupRC();
void SpecialKeys(int, int, int);
void RenderScene(void);

void drawFactory(GLfloat base, GLfloat height);

int main(int, char*[]);

#endif
