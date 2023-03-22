#include "castle.h"
#include "utils.h"

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

void createTower(GLUquadricObj *pObj, GLfloat posx, GLfloat posy, GLfloat posz) {
    glColor3f(0.35f, 0.35f, 0.35f);  
	glPushMatrix();
	glTranslatef(posx, posy, posz);
	glRotatef(-90.0f, 5.0f, 0.0f, 0.0f);
	gluCylinder(pObj, 0.2f, 0.2f, 1.5/2.0f, 26, 13);  
	glPopMatrix();
}

void createWall() {
    glRotatef(0, 0, 0, 0);
    glColor3f(0.55f, 0.55f, 0.55f);
	glPushMatrix();
	float x=0.77,y=2.7/2.2,z=0.3, translatex=-1.15, translatez=1.35;
	glTranslatef(translatex, y/4, translatez);
	// x = largura da parede
	// y = altura da parede
	// z = espessura
	glScalef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(translatex+x*0.5, 0.15, translatez);
	glScalef(x, y*1.32/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(translatex+x*0.5, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(translatex+x, y/4, translatez);
	glScalef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();
    
    glPushMatrix();
	glTranslatef(translatex+x*1.5, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(translatex+x*2, y/4, translatez);
	glScalef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(translatex+x*2.5, 0.15, translatez);
	glScalef(x, y*1.32/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(translatex+x*2.5, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(translatex+x*3, y/4, translatez);
	glScalef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();
}

void createWalls(GLfloat angulox, GLfloat anguloz, GLfloat translatex, GLfloat translatey, GLfloat translatez) {
	glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);
	float x=5.4,y=2.7/2.2,z=0.3;
    glRotatef(angulox, 0, anguloz, 0);
    glTranslatef(translatex, translatey+y/4, translatez);
	// glTranslatef(translatex, y/4, translatez);
    // x = largura da parede
    // y = altura da parede
    // z = espessura
	glScalef(x, y, z);
	glutSolidCube(0.5);
	glPopMatrix();

    x=0.77;
    y=2.7/2.2;
    z=0.3;
    
    glPushMatrix();
    glRotatef(angulox, 0, anguloz, 0);
	glTranslatef(translatex+0.7, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
    glRotatef(angulox, 0, anguloz, 0);
	glTranslatef(translatex, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();

    glPushMatrix();
    glRotatef(angulox, 0, anguloz, 0);
	glTranslatef(translatex-0.7, 0.25+y*0.325, translatez);
	glScalef(x, y/3, z);
	glutSolidCube(0.5);
	glPopMatrix();
}

void createTrees(GLUquadricObj *pObj, GLfloat posx, GLfloat posy, GLfloat posz) {
	glPushMatrix();
    glColor3f(0.7, 0.35, 0.25);
	glTranslatef(posx, posy, posz);
	glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
	gluCylinder(pObj, 0.05/2.0f, 0.05/2.0f, 0.3/2.0f, 26, 13);  
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(posx, posy+0.3, posz);
	glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
	gluCylinder(pObj, 0.0/2.0f, 0.13/2.0f, 0.38/2.0f, 26, 13);  
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posx, posy+0.4, posz);
	glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
	gluCylinder(pObj, 0.0/2.0f, 0.09/2.0f, 0.3/2.0f, 26, 13);  
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
	drawCube(0x7CFC00, 0.5, rotation, position, scale);

    // castle floor
	position = newCoordinate(0.0, 0.01, 0.0f);
	scale = newCoordinate(7.5f, 7.5f, 0.1f);
	rotation = newRotation(-90.0f, 90.0f, 0.0f, 0.0f);
	drawCube(0x808080, 0.5, rotation, position, scale);

    // create tower
    float translate_tower = 1.35;
    createTower(pObj, translate_tower, 0.0, translate_tower);
    createTower(pObj, -translate_tower, 0.0, translate_tower);
    createTower(pObj, translate_tower, 0.0, -translate_tower);
    createTower(pObj, -translate_tower, 0.0, -translate_tower);

    // create wall
    createWall();
    
    // crate walls
    createWalls(90.0,90.0, 0, 0.0, 1.35);
    createWalls(90.0,90.0, 0, 0.0, -1.35);
    createWalls(0.0,0.0, 0, 0.0, -1.35);

    // create trees
    for(int i=0; i < 10; i++){
        createTrees(pObj, i, 0.15 , i+2);
    }

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
