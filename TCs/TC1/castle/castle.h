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
static GLfloat cameraSpeed = 0.05f;

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
	// Grass
	0x261c06,
	// Mud
	0x135000,
	// Water
	0x010D14
};

const GLfloat grassSide = 15.0f;
const GLfloat waterSide = 9.8f;

extern Rotation rotation;
extern Coordinate position;
extern Coordinate coordinate;
extern Coordinate scale;

extern Cylinder cylinder;

extern float translateTower;

// Rotation
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Camera
static GLfloat zoom = -5.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int, int);

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC();

// Respond to arrow keys (rotate castle)
void SpecialKeys(int, int, int);

// Called to draw scene  
void RenderScene(void);

void createTower(GLUquadricObj* quad, GLfloat towerBase, GLfloat towerHeight, Coordinate position, bool hasFlag);
void drawBackWall(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawFrontWall(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawSideWall(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void createTree(GLUquadricObj*, Coordinate position);

int main(int, char*[]);

#endif
