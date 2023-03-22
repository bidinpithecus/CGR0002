#ifndef _castle_h_
#define _castle_h_

#include "utils.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

// Define the camera position and orientation
static GLfloat cameraPosition[3] = {0.0f, 0.0f, 5.0f};
static GLfloat cameraDirection[3] = {0.0f, 0.0f, -1.0f};
static GLfloat cameraUp[3] = {0.0f, 1.0f, 0.0f};
static GLfloat cameraSpeed = 0.05f;

static Rotation rotation;
static Coordinate position;
static Coordinate scale;

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

void createTower(GLUquadricObj*, GLfloat, GLfloat, GLfloat);

void createWall();

void createWalls(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void createTrees(GLUquadricObj*, GLfloat, GLfloat, GLfloat);

int main(int, char*[]);

#endif
