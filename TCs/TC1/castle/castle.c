#include "castle.h"
#include "utils.h"
#include <GL/gl.h>

Rotation rotation;
Coordinate position;
Coordinate coordinate;
Coordinate scale;
Cylinder cylinder;
float translateTower = 1.35;

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

void createTower(GLUquadricObj *pObj, Coordinate position) {
	glPushMatrix();
	GLfloat towerHeight = 1.0f;
	// Tower
	rotation = newRotation(-90.0f, 5.0f, 0.0f, 0.0f);
	cylinder = newCylinder(pObj, 0.2f, 0.2f, towerHeight, 26, 13);

	drawCylinder(colorPalette[4], cylinder, rotation, position);

	// Top
	cylinder = newCylinder(pObj, 0.0 / 2.0f, 0.50 / 2.0f, 0.7 / 2.0f, 26, 13);
	Coordinate topPosition = newCoordinate(position.x, (towerHeight * 0.99) + cylinder.height, position.z);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	drawCylinder(colorPalette[2], cylinder, rotation, topPosition);

	rotation = newRotation(-90.0f, 5.0f, 0.0f, 0.0f);
	topPosition.y *= 0.9f;
	cylinder = newCylinder(pObj, 0.03 / 2.0f, 0.03 / 2.0f, 0.8 / 2.0f, 26, 13);
	drawCylinder(colorPalette[2], cylinder, rotation, topPosition);

    rotation = newRotation(0, 0, 0, 0);
	scale = newCoordinate(0.70f, 0.25f, 0.1f);
	topPosition.x += ((scale.x / 4.0f) - (cylinder.base));
	topPosition.y += 0.8 / 2.0f;
	drawCube(colorPalette[0], CUBE_SIZE, rotation, topPosition, scale);

	glPopMatrix();
}

void drawFrontWall(GLfloat anguloX, GLfloat anguloZ, GLfloat translateX, GLfloat translateY, GLfloat translateZ) {
	glPushMatrix();
	coordinate = newCoordinate(5.4, 2.7 / 2.2, 0.3);
    rotation = newRotation(anguloX, 0, anguloZ, 0);

    position = newCoordinate(translateX * translateTower, translateY + coordinate.y / 4, translateZ * translateTower);
	scale = newCoordinate(coordinate.x, coordinate.y, coordinate.z);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

    coordinate = newCoordinate(0.77, 2.7 / 2.2, 0.3);
	scale = newCoordinate(coordinate.x, coordinate.y / 3, coordinate.z);

	position = newCoordinate(translateX * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	coordinate = newCoordinate(0.77, 2.7 / 2.2, 0.3);
	scale = newCoordinate(coordinate.x, coordinate.y / 3, coordinate.z);

	position = newCoordinate(-0.5 * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	position = newCoordinate(0.5 * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);
	glPopMatrix();
}

void drawSideWall(GLfloat anguloX, GLfloat anguloZ, GLfloat translateX, GLfloat translateY, GLfloat translateZ) {
	glPushMatrix();
	coordinate = newCoordinate(5.4, 2.7 / 2.2, 0.3);
    rotation = newRotation(anguloX, 0, anguloZ, 0);

    position = newCoordinate(translateX * translateTower, translateY + coordinate.y / 4, translateZ * translateTower);
	scale = newCoordinate(coordinate.x, coordinate.y, coordinate.z);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

    coordinate = newCoordinate(0.77, 2.7 / 2.2, 0.3);
	scale = newCoordinate(coordinate.x, coordinate.y / 3, coordinate.z);

	position = newCoordinate(translateX * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower);
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	coordinate = newCoordinate(0.77, 2.7 / 2.2, 0.3);
	scale = newCoordinate(coordinate.x, coordinate.y / 3, coordinate.z);

	position = newCoordinate(translateX * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower + (coordinate.x));
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);

	position = newCoordinate(translateX * translateTower, 0.25 + coordinate.y * 0.325, translateZ * translateTower - (coordinate.x));
	drawCube(colorPalette[0], CUBE_SIZE, rotation, position, scale);
	glPopMatrix();
}

void createTrees(GLUquadricObj *pObj, GLfloat posX, GLfloat posY, GLfloat posZ) {
	glPushMatrix();
	position = newCoordinate(posX, posY, posZ);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	cylinder = newCylinder(pObj, 0.05 / 2.0f, 0.05 / 2.0f, 0.3 / 2.0f, 26, 13);
	drawCylinder(colorPalette[2], cylinder, rotation, position);

	position = newCoordinate(posX, posY + 0.3, posZ);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	cylinder = newCylinder(pObj, 0.0 / 2.0f, 0.13 / 2.0f, 0.38 / 2.0f, 26, 13);
	drawCylinder(colorPalette[3], cylinder, rotation, position);

	position = newCoordinate(posX, posY + 0.4, posZ);
	rotation = newRotation(90.0f, 5.0f, 0.0f, 0.0f);
	cylinder = newCylinder(pObj, 0.0 / 2.0f, 0.09 / 2.0f, 0.3 / 2.0f, 26, 13);
	drawCylinder(colorPalette[3], cylinder, rotation, position);
	glPopMatrix();
}

// Called to draw scene  
void RenderScene(void){  
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

	// floor
	position = newCoordinate(0.0, 0.0, 0.0);
	scale = newCoordinate(15.0f, 15.0f, 0.1f);
	rotation = newRotation(-90.0f, 90.0f, 0.0f, 0.0f);
	drawCube(0x135000, CUBE_SIZE, rotation, position, scale);

	// water
	position = newCoordinate(0.0, 0.0, 0.0);
	scale = newCoordinate(9.8f, 9.8f, 0.101f);
	rotation = newRotation(-90.0f, 90.0f, 0.0f, 0.0f);
	drawCube(0x010D14, CUBE_SIZE, rotation, position, scale);

    // castle floor
	position = newCoordinate(0.0, 0.01, 0.0f);
	scale = newCoordinate(6.8f, 6.8f, 0.1008f);
	rotation = newRotation(-90.0f, 90.0f, 0.0f, 0.0f);
	drawCube(0x808080, CUBE_SIZE, rotation, position, scale);

    // create tower
    createTower(pObj, newCoordinate(translateTower, 0.0, translateTower));
    createTower(pObj, newCoordinate(-translateTower, 0.0, translateTower));
    createTower(pObj, newCoordinate(translateTower, 0.0, -translateTower));
    createTower(pObj, newCoordinate(-translateTower, 0.0, -translateTower));

    // crate walls
    drawSideWall(90.0,90.0, -1, 0.0, 0);
    drawSideWall(90.0,90.0, 1, 0.0, 0);
    drawFrontWall(0.0,0.0, 0, 0.0, -1);
    drawFrontWall(0.0,0.0, 0, 0.0, 1);

    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  
}

int main(int argc, char *argv[]) {
	// seed the random number generator with current time
	srand(time(0));
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
