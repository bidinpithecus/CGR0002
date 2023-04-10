#include "snowman.h"
#include "utils.h"

// Define the camera position and orientation
GLfloat cameraPosition[3] = {0.0f, 0.0f, 5.0f};
GLfloat cameraDirection[3] = {0.0f, 0.0f, -1.0f};
GLfloat cameraUp[3] = {0.0f, 1.0f, 0.0f};
GLfloat cameraSpeed = 0.05f;

int color = 0x000000;

Cylinder cylinder;
Disk disk;
Sphere sphere;

Position position;
Rotation rotation;

void timer(int value) {
	xRot -= 5.0f;
	xRot = (GLfloat)((const int)xRot % 360);

    glutPostRedisplay();  // update display
    glutTimerFunc(70, timer, 0);  // call timer function after 50ms
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h) {
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0) {
		h = 1;
	}
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Produce the perspective projection
	gluPerspective(35.0f, fAspect, 1.0, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Respond to some other keys (move camera and zoom)
void keyboardCallback(unsigned char key, int x, int y) {
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

// Called to draw scene
void RenderScene(void) {
	// Quadric Object
	GLUquadricObj *pObj;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
              cameraPosition[0] + cameraDirection[0], cameraPosition[1] + cameraDirection[1], cameraPosition[2] + cameraDirection[2],
              cameraUp[0], cameraUp[1], cameraUp[2]);

	// Save the matrix state and do the rotations
	glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, zoom);
	glRotatef(yRot, 1.0f, 0.0f, 0.0f);
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);

	// Draw something
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	// hat
	color = 0x000000;
	cylinder = newCylinder(pObj, 0.2f, 0.2f, 0.35f, 50, 150);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, 1.5, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	// hat top
	color = 0x000000;
	disk = newDisk(pObj, 0.0, 0.2, 1000, 10);
	rotation = newRotation(-90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, 1.5, 0.0);
	drawDisk(color, disk, rotation, position);

	// brim
	color = 0x000000;
	cylinder = newCylinder(pObj, 0.3f, 0.3f, 0.05f, 50, 150);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, 1.17, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	// brim top
	color = 0x000000;
	disk = newDisk(pObj, 0.0, 0.3, 1000, 10);
	rotation = newRotation(-90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, 1.15, 0.0);
	drawDisk(color, disk, rotation, position);

	// brim down
	color = 0x000000;
	disk = newDisk(pObj, 0.0, 0.3, 1000, 10);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, 1.15, 0.0);
	drawDisk(color, disk, rotation, position);

	// Head
	color = 0xFFFFFF;
	sphere = newSphere(pObj, 0.24f, 26, 13);
	position = newPosition(0.0f, 1.0f, 0.0f);
	drawSphere(color, sphere, position);

	// eye left
	color = 0x000000;
	sphere = newSphere(pObj, 0.048f, 26, 13);
	position = newPosition(0.07f, 1.06f, 0.18f);
	drawSphere(color, sphere, position);

	// eye right
	color = 0x000000;
	sphere = newSphere(pObj, 0.048f, 26, 13);
	position = newPosition(-0.07f, 1.06f, 0.18f);
	drawSphere(color, sphere, position);

	// Nose
	color = 0xED9121;
	cylinder = newCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
	rotation = newRotation(0.0f, 0.0f, 0.0f, 0.0f);
	position = newPosition(0.0f, 1.0f, 0.2f);
	drawCylinder(color, cylinder, rotation, position);

	// scarf
	color = 0x205C28;
	cylinder = newCylinder(pObj, 0.21f, 0.21f, 0.08f, 50, 150);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0f, 0.9f, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x205C28;
	cylinder = newCylinder(pObj, 0.04f, 0.04f, 0.2f, 50, 150);
	rotation = newRotation(-90.0f, -15.0f, 15.0f, 0.0f);
	position = newPosition(-0.05, 0.9f, 0.15f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x205C28;
	cylinder = newCylinder(pObj, 0.04f, 0.04f, 0.2f, 50, 150);
	rotation = newRotation(-95.0f, -15.0f, -15.0f, 0.0f);
	position = newPosition(0.06f, 0.9f, 0.15f);
	drawCylinder(color, cylinder, rotation, position);

	// body
	color = 0xFFFFFF;
	sphere = newSphere(pObj, 0.29f, 26, 13);
	position = newPosition(0.0, 0.6, 0.0);
	drawSphere(color, sphere, position);

	// left arm
	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13);
	rotation = newRotation(-150.0f, 5.0f, 0.5f, 5.0f);
	position = newPosition(0.23, 0.7, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.01f, 0.005f, 0.2f, 26, 13);
	rotation = newRotation(-90.0f, 5.0f, 0.0f, 5.0f);
	position = newPosition(0.65, 0.91, 0.038f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13);
	rotation = newRotation(-150.0f, 5.0f, 0.5f, 5.0f);
	position = newPosition(0.23, 0.7, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.01f, 0.005f, 0.2f, 26, 13);
	rotation = newRotation(-180.0f, 5.0f, 0.0f, 5.0f);
	position = newPosition(0.65, 0.91, 0.038f);
	drawCylinder(color, cylinder, rotation, position);

	// right arm
	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.01f, 0.02f, 0.5f, 26, 13);
	rotation = newRotation(145.0f, 5.0f, 0.5f, 5.0f);
	position = newPosition(-0.72, 0.89f, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.005f, 0.01f, 0.2f, 26, 13);
	rotation = newRotation(-240.0f, 5.0f, 0.0f, 5.0f);
	position = newPosition(-0.98+0.15, 1.22-0.22, -0.02f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0x4B3621;
	cylinder = newCylinder(pObj, 0.005f, 0.01f, 0.2f, 26, 13);
	rotation = newRotation(-240.0f, 10.0f, 10.0f, 10.0f);
	position = newPosition(-1.04+0.15, 1.1-0.22, 0.03f);
	drawCylinder(color, cylinder, rotation, position);

	// first button
	color = 0x000000;
	sphere = newSphere(pObj, 0.048f, 26, 13);
	position = newPosition(0.0f, 0.7f, 0.23f);
	drawSphere(color, sphere, position);

	// second button2
	color = 0x000000;
	sphere = newSphere(pObj, 0.048f, 26, 13);
	position = newPosition(0.0, 0.6, 0.25);
	drawSphere(color, sphere, position);

	// third button3
	color = 0x000000;
	sphere = newSphere(pObj, 0.048f, 26, 13);
	position = newPosition(0.0, 0.5, 0.23);
	drawSphere(color, sphere, position);

	// feet
	color = 0xFFFFFF;
	sphere = newSphere(pObj, 0.34f, 26, 13);
	position = newPosition(0.0, 0.17, 0.0);
	drawSphere(color, sphere, position);

	// floor
	color = 0xFFFFFF;
	disk = newDisk(pObj, 0.0, 3.5, 1000, 10);
	rotation = newRotation(-90.0f, 50.0f, 0.0f, 0.0f);
	position = newPosition(0.0, -0.18, 0.0);
	drawDisk(color, disk, rotation, position);

	color = 0xFFFFFF;
	disk = newDisk(pObj, 0.0, 3.5, 1000, 10);
	rotation = newRotation(90.0f, 50.0f, 0.0f, 0.0f);
	position = newPosition(0.0, -0.18, 0.0);
	drawDisk(color, disk, rotation, position);

	// Snowflakes
	fillDome(pObj, 3.5);

	double plane[] = {0.0, 1.0, 0.0, 0.2};
	glClipPlane(GL_CLIP_PLANE0, plane);
	glEnable(GL_CLIP_PLANE0);

	glPushMatrix();
   	// draw the translucent sphere
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.35);
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluSphere(quadric, 3.5, 50, 50);
	gluDeleteQuadric(quadric);
	glDisable(GL_BLEND);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();

	// floor
	color = 0xC54245;
	cylinder = newCylinder(pObj, 3.5f, 3.5f, 0.66f, 50, 150);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0f, -0.19f, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	color = 0xC54245;
	disk = newDisk(pObj, 0.0, 3.5f, 1000, 10);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	position = newPosition(0.0, -0.85f, 0.0);
	drawDisk(color, disk, rotation, position);

	glPopMatrix();

	// Buffer swap
	glutSwapBuffers();
}

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void SetupRC() {
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

	glEnable(GL_DEPTH_TEST);  // Hidden surface removal
	glFrontFace(GL_CCW);      // Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);// Do not calculate inside

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

	Rgb rgbColor = hexTo3f(0xE8DACC);

	// Off-white background
	glClearColor(rgbColor.red, rgbColor.green, rgbColor.blue, 1.0f);
}

// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y) {
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
			xRot -= 2.0f;
			break;
	}

	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	// seed the random number generator with current time

	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Snowman");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(0, timer, 0);
	SetupRC();
	glutMainLoop();

	return 0;
}
