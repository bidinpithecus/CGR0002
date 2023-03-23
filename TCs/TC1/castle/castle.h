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

const int colorPalette[] = { 0x292929, 0x604646, 0x927A61, 0x515151, 0x39405E };
// const int colorPalette[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0x00FFFF };

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

void createTower(GLUquadricObj*, Coordinate position);

void drawFrontWall(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void drawSideWall(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void createTrees(GLUquadricObj*, GLfloat, GLfloat, GLfloat);

int main(int, char*[]);

#endif
