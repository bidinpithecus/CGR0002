#include "snowman.h"

// Define the camera position and orientation
GLfloat cameraDirection[3] = { 0.0f, 0.0f, -1.0f };
GLfloat cameraPosition[3] = { 0.0f, -0.75f, 5.0f };
GLfloat cameraUp[3] = { 0.0f, 1.0f, 0.0f };
GLfloat cameraSpeed = 0.05f;
GLfloat zoom = -4.0f;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

int color = 0x000000;

Cylinder cylinder;
Disk disk;
Sphere sphere;

Position position;
Rotation rotation;

void drawArm(double bodyRadius, double bodyY, GLUquadricObj* pObj, int side) {
	color = 0x4B3621;
	GLfloat armSize;
	cylinder = newCylinder(pObj, bodyRadius * 0.075f, bodyRadius * (0.075f / 2.0), bodyRadius * (0.075f / 2.0) * 50, 26, 13);
	rotation = newRotation(120.0f * side, 5.0f * side, 0.0f, 5.0f);
	position = newPosition(bodyRadius * 0.75 * side, bodyY * 0.25, 0.0f);
	drawCylinder(color, cylinder, rotation, position);

	armSize = cylinder.height;

	position = newPosition(armSize * 1.1 * side, position.y - (armSize / 1.7), armSize * 0.25);
	rotation = newRotation(180 * side, 5.0f * side, 0.0f, 5.0f);
	cylinder = newCylinder(pObj, cylinder.top, cylinder.top / 2.0, cylinder.height / 3.0, 26, 13);
	drawCylinder(color, cylinder, rotation, position);

	rotation.angle = 60 * side;
	drawCylinder(color, cylinder, rotation, position);
}

// Called to draw scene
void drawScene(void) {
	Rgb rgbColor;
	GLUquadricObj *pObj;
	GLfloat globeRadius = 7.5f;
	GLfloat globeOpening = globeRadius * 0.714285714;
	GLfloat floorHeight = globeRadius * (0.35);
	GLfloat floorRadius = sqrt((pow(globeRadius, 2) - pow(floorHeight, 2)));
	GLfloat glassMult;
	GLfloat headY;
	GLfloat bodyY;
	GLfloat bodyRadius;

	double bottomPlane[] = { 0.0, 1.0, 0.0, globeOpening };
	double topPlane[] = { 0.0, -1.0, 0.0, -floorHeight };

	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	// floor
	color = 0xFFFFFF;
	position = newPosition(0.0, -floorHeight, 0.0);
	disk = newDisk(pObj, 0.0, floorRadius, 1000, 10);
	rotation = newRotation(-90.0f, 1.0f, 0.0f, 0.0f);
	drawDisk(color, disk, rotation, position);
	rotation.angle = 90.0f;
	drawDisk(color, disk, rotation, position);

	// Enable the clipping planes
	glClipPlane(GL_CLIP_PLANE0, bottomPlane);
	glClipPlane(GL_CLIP_PLANE1, topPlane);
	glEnable(GL_CLIP_PLANE0);
	glEnable(GL_CLIP_PLANE1);

	glPushMatrix();
		gluSphere(pObj, globeRadius * 0.9999, 104, 52);
		glDisable(GL_CLIP_PLANE0);
		glDisable(GL_CLIP_PLANE1);
	glPopMatrix();

	position.y = -globeOpening;
	disk.outer = sqrt((pow(globeRadius, 2) - pow(globeOpening, 2)));
	drawDisk(color, disk, rotation, position);

	// snowman's feet
	sphere = newSphere(pObj, globeRadius * (1 / 8.0), 104, 52);
	position.y = -floorHeight + (sphere.radius * 0.9);
	drawSphere(color, sphere, position);

	// snowman's body
	bodyRadius = sphere.radius * 0.85;
	sphere = newSphere(pObj, bodyRadius, 104, 52);
	bodyY = position.y + (sphere.radius * 1.7);
	position.y = bodyY;
	drawSphere(color, sphere, position);

	// snowman's head
	sphere = newSphere(pObj, sphere.radius * 0.85, 104, 52);
	headY = position.y + (sphere.radius * 1.6);
	position.y = headY;
	drawSphere(color, sphere, position);
	glassMult = sphere.radius * 0.75;

	position.y += sphere.radius;
	// snowman's bucket
	color = 0x261614;
	cylinder = newCylinder(pObj, sphere.radius * 0.95f, sphere.radius * 1.05f, sphere.radius * 0.6, 50, 150);
	position.y += (cylinder.height / 3);
	position.y *= 0.95;
	drawCylinder(color, cylinder, rotation, position);

	// bucket's top
	rotation.angle = -90;
	disk.outer = cylinder.base;
	drawDisk(color, disk, rotation, position);

	// bucket's brim
	cylinder.base = cylinder.base * 1.3;
	position.y -= cylinder.height * 1.5;
	cylinder.height *= 0.5;
	color = 0x211412;
	drawCylinder(color, cylinder, rotation, position);

	// Draw the sunglasses
	glPushMatrix();
		rgbColor = hexTo3f(0x601A16);
		glTranslatef(0, headY * (3 / 4.0), sphere.radius);
		// set the color to black
		glColor3f(rgbColor.red, rgbColor.green, rgbColor.blue);
		// set the line width to 2
		glLineWidth(2.0f);

		// Draw the left lens
		glBegin(GL_POLYGON);
			glVertex3f(-0.75 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(-0.125 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(-0.125 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(-0.75 * glassMult, 0.625 * glassMult, 0);
		glEnd();

		// Draw the right lens
		glBegin(GL_POLYGON);
			glVertex3f(0.125 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(0.75 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(0.75 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(0.125 * glassMult, 0.625 * glassMult, 0);
		glEnd();

		// Draw the bridge
		glBegin(GL_LINES);
			rgbColor = hexTo3f(0x76655A);
			glColor3f(rgbColor.red, rgbColor.green, rgbColor.blue);
			// set the line width to 10
			glLineWidth(10.0f);

			// Draw the left lens
			glVertex3f(-0.75 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(-0.125 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(-0.75 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(-0.125 * glassMult, 0.625 * glassMult, 0);

			glVertex3f(-0.75 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(-0.75 * glassMult, 0.25 * glassMult, 0);

			glVertex3f(-0.125 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(-0.125 * glassMult, 0.25 * glassMult, 0);

			// Draw the right lens
			glVertex3f(0.125 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(0.75 * glassMult, 0.25 * glassMult, 0);
			glVertex3f(0.125 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(0.75 * glassMult, 0.625 * glassMult, 0);

			glVertex3f(0.125 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(0.125 * glassMult, 0.25 * glassMult, 0);

			glVertex3f(0.75 * glassMult, 0.625 * glassMult, 0);
			glVertex3f(0.75 * glassMult, 0.25 * glassMult, 0);

			glVertex3f(-0.125 * glassMult, 0.425 * glassMult, 0);
			glVertex3f(0.125 * glassMult, 0.425 * glassMult, 0);
		glEnd();
	glPopMatrix();

	// Nose
	color = 0xED9121;
	cylinder = newCylinder(pObj, sphere.radius * 0.1, 0.0f, sphere.radius * 0.8, 26, 13);
	rotation.angle = 0;
	position = newPosition(0.0f, headY * 0.975, sphere.radius);
	drawCylinder(color, cylinder, rotation, position);

	drawArm(bodyRadius, bodyY, pObj, RIGHT);
	drawArm(bodyRadius, bodyY, pObj, LEFT);

	// draw the translucent sphere
	glPushMatrix();
		glClipPlane(GL_CLIP_PLANE0, bottomPlane);
		glEnable(GL_CLIP_PLANE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		rgbColor = hexTo3f(0x0c1445);
		glColor4f(rgbColor.red, rgbColor.green, rgbColor.blue, 0.2);
		gluQuadricDrawStyle(pObj, GLU_FILL);
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluSphere(pObj, globeRadius, 104, 52);
		gluDeleteQuadric(pObj);
		glDisable(GL_BLEND);
		glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Snowie");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	setupRC();
	glutMainLoop();

	return 0;
}
