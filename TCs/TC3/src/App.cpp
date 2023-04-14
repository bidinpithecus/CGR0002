#include "App.hpp"
#include "Camera.hpp"
#include "Color.hpp"

#define UNUSED __attribute__((unused))

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int width = WINDOW_WIDTH;
int height = WINDOW_HEIGHT;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

Camera camera = Camera(Position(0, 0, -1), Position(0.0f, -0.75f, 5.0f), Position(0.0f, 1.0f, 0.0f), Position(0, 0, 0), 0.05f, -4.0f);

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
			camera.setPosition(Position(camera.getPosition().getX(), camera.getPosition().getY() + camera.getSpeed(), camera.getPosition().getZ()));
			break;

		// Move the camera backward when the "S" key is pressed
		case 's':
		case 'S':
			camera.setPosition(Position(camera.getPosition().getX(), camera.getPosition().getY() - camera.getSpeed(), camera.getPosition().getZ()));
			break;

		// Move the camera to the left when the "A" key is pressed
		case 'a':
		case 'A':
			camera.setPosition(Position(camera.getPosition().getX() - camera.getSpeed(), camera.getPosition().getY(), camera.getPosition().getZ()));
			break;

		// Move the camera to the right when the "D" key is pressed
		case 'D':
		case 'd':
			camera.setPosition(Position(camera.getPosition().getX() + camera.getSpeed(), camera.getPosition().getY(), camera.getPosition().getZ()));
			break;

		// Zoom out when the "z" key is pressed
		case 'z':
			camera.setZoom(camera.getZoom() - (camera.getSpeed() * 2));
			break;

		// Zoom in when the "z" key is pressed
		case 'Z':
			camera.setZoom(camera.getZoom() + (camera.getSpeed() * 2));
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
	gluLookAt(camera.getPosition().getX(), camera.getPosition().getY(), camera.getPosition().getZ(), camera.getPosition().getX() + camera.getDirection().getX(), camera.getPosition().getY() + camera.getDirection().getY(), camera.getPosition().getZ() + camera.getDirection().getZ(), camera.getUp().getX(), camera.getUp().getY(), camera.getUp().getZ());

	// Save the matrix state and do the rotations
	glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, camera.getZoom());
	glRotatef(camera.getRotation().getY(), 1.0f, 0.0f, 0.0f);
	glRotatef(camera.getRotation().getX(), 0.0f, 1.0f, 0.0f);
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
void setupRC()
{
    // Set up OpenGL rendering context

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set counter-clockwise polygons to face out
    glFrontFace(GL_CCW);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Set up and enable light 0 for ambient and diffuse light
    GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Set up and enable light 1 for moonlight
    GLfloat moonPosition[] = {-10.f, 5.0f, 5.0f, 1.0f};
    GLfloat moonDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonEmission[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonConstantAttenuation = 1.0f; // Constant attenuation factor
    GLfloat moonLinearAttenuation = 0.0f; // Linear attenuation factor
    GLfloat moonQuadraticAttenuation = 0.01f; // Quadratic attenuation factor, adjust as needed

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, moonDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, moonSpecular);
    glLightfv(GL_LIGHT1, GL_EMISSION, moonEmission);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, moonConstantAttenuation);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, moonLinearAttenuation);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, moonQuadraticAttenuation);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Set clear color to off-white for background
    Color backgroundColor = Color(0x555555);
    glClearColor(backgroundColor.getRed(), backgroundColor.getGreen(), backgroundColor.getBlue(), 1.0f);
}

// Respond to arrow keys (rotate snowman)
void specialKeyPressed(int key, UNUSED int x, UNUSED int y) {
	float rotationSpeed = camera.getSpeed() * 100;
	switch (key) {
		case GLUT_KEY_DOWN:
			camera.setRotation(Position(camera.getRotation().getX(), camera.getRotation().getY() - rotationSpeed, camera.getRotation().getZ()));
			break;

		case GLUT_KEY_UP:
			camera.setRotation(Position(camera.getRotation().getX(), camera.getRotation().getY() + rotationSpeed, camera.getRotation().getZ()));
			break;

		case GLUT_KEY_LEFT:
			camera.setRotation(Position(camera.getRotation().getX() + rotationSpeed, camera.getRotation().getY(), camera.getRotation().getZ()));
			break;

		case GLUT_KEY_RIGHT:
			camera.setRotation(Position(camera.getRotation().getX() - rotationSpeed, camera.getRotation().getY(), camera.getRotation().getZ()));
			break;

		case GLUT_KEY_F11:
			toggleFullScreen();
			break;
	}

	camera.setRotation(Position((int) camera.getRotation().getX() % 360, (int) camera.getRotation().getY() % 360, camera.getRotation().getZ()));

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
