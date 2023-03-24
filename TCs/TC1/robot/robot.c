#include "robot.h"
#include "utils.h"
#include <GL/glu.h>

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

// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.
void SetupRC() {
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
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

// Respond to arrow keys (rotate castle)
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
			xRot -= 5.0f;
			break;
	}

	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);
	
	// Refresh the Window
	glutPostRedisplay();
}

void drawCable(GLUquadricObj* quadObj, float base, float yPosition, float rightShift, float forwardShift) {
	float height = (yPosition + (base / 4)) * 3;
	float wireSizeMult = 0.35;

	position = newCoordinate(rightShift * height / 8, yPosition - (base / 4), forwardShift * height / 8);
	rotation = newRotation(90, 1, 0, 0);
	cylinder = newCylinder(quadObj, base * 0.05, base * 0.05, yPosition * wireSizeMult, 26, 13);
	drawCylinder(colorPalette[1], cylinder, rotation, position);

	position.y = (yPosition * (1 - wireSizeMult)) - (base / 4);
	cylinder = newCylinder(quadObj, base * 0.25, base * 0.25, position.y * 0.05, 26, 13);
	drawCylinder(colorPalette[2], cylinder, rotation, position);

	rotation.angle = -90.0;
	disk = newDisk(quadObj, 0.0, base * 0.25, 1000, 10);
	drawDisk(colorPalette[2], disk, rotation, position);
	rotation.angle = +90.0;
	position.y /= 1.05;
	drawDisk(colorPalette[2], disk, rotation, position);
}

void drawFactory(GLfloat base, GLfloat height) {
	GLUquadricObj* quadObj;
	rotation = newRotation(0.0, 0.0, 0.0, 0.0);
	float beamsY = (height / 3) - (base / 4);

	quadObj = gluNewQuadric();
	gluQuadricNormals(quadObj, GLU_SMOOTH);

	// floor and ceiling
	position = newCoordinate(0.0, 0.0f, 0.0);
	scale = newCoordinate(height, base, height);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);
	position.y = (height) / 2;
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	// grass
	position.x = height / 2;
	position.y = 0;
	drawCube(colorPalette[3], CUBE_SIZE, rotation, position, scale);
	position.x = -height / 2;
	position.y = 0;
	drawCube(colorPalette[3], CUBE_SIZE, rotation, position, scale);
	position.x = height / 2;
	position.y = 0;
	position.z = -height / 2;
	drawCube(colorPalette[3], CUBE_SIZE, rotation, position, scale);
	position.x = -height / 2;
	position.y = 0;
	position.z = -height / 2;
	drawCube(colorPalette[3], CUBE_SIZE, rotation, position, scale);
	position.x = 0;
	position.y = 0;
	position.z = -height / 2;
	drawCube(colorPalette[3], CUBE_SIZE, rotation, position, scale);

	// side walls
	position = newCoordinate((-height / 4) + (base / 4), (height / 4) - (base / 4), 0.0);
	scale = newCoordinate(base, height, height);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);
	position.x = (height / 4) - (base / 4);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	// back wall
	position = newCoordinate(0.0, (height / 4) - (base / 4), (-height / 4) + (base / 4));
	scale = newCoordinate(height, height, base);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	// beams
	position = newCoordinate(0, (height / 3) - (base / 4), 0.0);
	scale = newCoordinate((height) * 0.99f, base, base);
	drawCube(colorPalette[2], CUBE_SIZE, rotation, position, scale);
	position.z = height / 8;
	drawCube(colorPalette[2], CUBE_SIZE, rotation, position, scale);
	position.z = -height / 8;
	drawCube(colorPalette[2], CUBE_SIZE, rotation, position, scale);

	// wires
	drawCable(quadObj, base, beamsY, -0.75, -1);
	drawCable(quadObj, base, beamsY, 0.75, -1);

	drawCable(quadObj, base, beamsY, -0.75, 0);
	drawCable(quadObj, base, beamsY, 0.75, 0);

	drawCable(quadObj, base, beamsY, -0.75, 1);
	drawCable(quadObj, base, beamsY, 0.75, 1);
}

void drawRobot(float totalHeight) {
	// Defining and initializing robot parts
	GLUquadricObj* robotParts[NUM_PARTS_ROBOT];
	for (int i = 0; i < NUM_PARTS_ROBOT; i++) {
		robotParts[i] = gluNewQuadric();
		gluQuadricNormals(robotParts[i], GLU_SMOOTH);
	}
	// head is one eighth of total body
	GLfloat headRadius = (totalHeight * (1.0 / 8.0)) / 2;

	// head
	position = newCoordinate(0, 0, 0);
	sphere = newSphere(robotParts[HEAD], headRadius, 26, 13);
	drawSphere(colorPalette[4], sphere, position);

}


// Called to draw scene  
void RenderScene(void) {
	// Quadric Object
	GLUquadricObj *pObj;

	// Draw something
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

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


	drawFactory(factoryBase, factoryHeight);
	drawRobot(factoryHeight / 4);


    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  
}

int main(int argc, char *argv[]) {
	float factoryBase = 1.0f;
	float factoryHeight = 20.0f;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Castle");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0; 
}
