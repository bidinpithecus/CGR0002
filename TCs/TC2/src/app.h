#ifndef _app_h_
#define _app_h_

#include "utils.h"

extern GLfloat cameraDirection[3];
extern GLfloat cameraPosition[3];
extern GLfloat cameraUp[3];
extern GLfloat cameraSpeed;
extern GLfloat zoom;
extern GLfloat xRot;
extern GLfloat yRot;

extern int height;
extern int width;
extern int xPos;
extern int yPos;
extern bool isFullScreen;

void drawScene();
void initScene();
void finishScene();
void normalKeyPressed(unsigned char key, int x, int y);
void renderScene(void);
void setupRC();
void specialKeyPressed(int key, int x, int y);
void toggleFullScreen();
void resize(int x, int y);

#endif
