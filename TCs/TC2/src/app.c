#include "app.h"

#define UNUSED __attribute__((unused))

// Change viewing volume and viewport.  Called when window is resized
void resize(int width, int height) {
	GLfloat fAspect;

	// Prevent a divide by zero
	if (height == 0) {
		height = 1;
	}

	// Set Viewport to window dimensions
	glViewport(0, 0, width, height);
	fAspect = (GLfloat)width / (GLfloat)height;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
	gluPerspective(45.0f, fAspect, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Respond to some other keys (move camera and zoom)
void normalKeyPressed(unsigned char key, UNUSED int x, UNUSED int y) {
    switch(key) {
        // Move the camera forward when the "W" key is pressed
        case 'w':
        case 'W':
            cameraPosition[1] += cameraSpeed;
            break;

        // Move the camera backward when the "S" key is pressed
        case 's':
        case 'S':
            cameraPosition[1] -= cameraSpeed;
            break;

        // Move the camera to the left when the "A" key is pressed
        case 'a':
        case 'A':
            cameraPosition[0] -= cameraSpeed;
            break;

        // Move the camera to the right when the "D" key is pressed
        case 'D':
        case 'd':
            cameraPosition[0] += cameraSpeed;
            break;

		// Zoom out when the "z" key is pressed
		case 'z':
			zoom -= cameraSpeed * 2;
			break;

		// Zoom in when the "z" key is pressed
		case 'Z':
			zoom += cameraSpeed * 2;
			break;

        // Exit the program when the "ESC" key is pressed
        case 27:
            exit(0);
            break;
    }

    // Redraw the scene
    glutPostRedisplay();
}

void initScene() {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], cameraPosition[0] + cameraDirection[0], cameraPosition[1] + cameraDirection[1], cameraPosition[2] + cameraDirection[2], cameraUp[0], cameraUp[1], cameraUp[2]);

	// Save the matrix state and do the rotations
	glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, zoom);
	glRotatef(yRot, 1.0f, 0.0f, 0.0f);
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);
}

void finishScene() {
	glPopMatrix();
	glutSwapBuffers();
}

void renderScene() {
	initScene();
	drawScene();
	finishScene();
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void setupRC() {
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

	// Hidden surface removal
	glEnable(GL_DEPTH_TEST);
	// Counter clock-wise polygons face out
	glFrontFace(GL_CCW);
	// Do not calculate inside
	glEnable(GL_CULL_FACE);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Main background color
	Rgb backgroundColor = hexTo3f(0x555555);

	// Off-white background
	glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 1.0f);
}

// Respond to arrow keys (rotate snowman)
void specialKeyPressed(int key, UNUSED int x, UNUSED int y) {
	switch (key) {
		case GLUT_KEY_DOWN:
			yRot -= 5.0f;
			break;

		case GLUT_KEY_UP:
			yRot += 5.0f;
			break;

		case GLUT_KEY_LEFT:
			xRot += 5.0f;
			break;

		case GLUT_KEY_RIGHT:
			xRot -= 5.0f;
			break;

		case GLUT_KEY_F11:
			toggleFullScreen();
			break;
	}

	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}

void toggleFullScreen() {
	if (isFullScreen) {
		glutReshapeWindow(width, height);
		glutPositionWindow(xPos, yPos);
	} else {
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);
		xPos = glutGet(GLUT_WINDOW_X);
		yPos = glutGet(GLUT_WINDOW_Y);

		glutFullScreen();
	}
	isFullScreen = !isFullScreen;
}
