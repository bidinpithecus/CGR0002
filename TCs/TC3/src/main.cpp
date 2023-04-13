#include "Camera.hpp"
#include "snowman.h"
// #include "particle.h"
#include "Color.hpp"
#include "Shapes.hpp"
#include "Helpers.hpp"
#include <math.h>
#include <time.h>

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;

Color color;

Cylinder cylinder;
Disk disk;
Sphere sphere;

Position position;
Rotation rotation;

GLUquadricObj *pObj;
const GLfloat globeRadius = 3.5;
const GLfloat globeOpeningHeight = globeRadius * 0.714285714;
const GLfloat globeOpeningRadius = sqrt(pow(globeRadius, 2) - pow(globeOpeningHeight, 2));
const GLfloat floorHeight = globeRadius * (0.35);
const GLfloat floorRadius = sqrt((pow(globeRadius, 2) - pow(floorHeight, 2)));
const GLfloat feetRadius = globeRadius * (1 / 8.0);
const GLfloat bodyRadius = feetRadius * 0.85;
const GLfloat headRadius = bodyRadius * 0.85;
const GLfloat feetY = -floorHeight + (feetRadius * 0.9);
const GLfloat bodyY = -floorHeight + (feetRadius * 0.9) + (bodyRadius * 1.7);
const GLfloat headY = bodyRadius + (headRadius * 1.6);
const GLfloat bucketHeight = headRadius * 0.6;
const GLfloat glassMult = headRadius * 0.75;
const GLfloat eyeSize = headRadius * 0.1;
const double bottomPlane[] = { 0.0, 1.0, 0.0, globeOpeningHeight };
const double topPlane[] = { 0.0, -1.0, 0.0, -floorHeight };

void drawArm(double bodyRadius, double bodyY, GLUquadricObj* pObj, int side) {
	color = Color(0x4B3621);
	GLfloat armSize;
	position = Position(bodyRadius * 0.75 * side, bodyY * 0.25, 0.0f);
	rotation = Rotation(120.0f * side, 5.0f * side, 0.0f, 5.0f);
	cylinder = Cylinder(pObj, bodyRadius * 0.075f, bodyRadius * (0.075f / 2.0), bodyRadius * (0.075f / 2.0) * 50, 26, 13, rotation, position, color);
	cylinder.draw();

	armSize = cylinder.getHeight();

	position = Position(armSize * 1.1 * side, position.getY() - (armSize / 1.7), armSize * 0.25);
	rotation = Rotation(180 * side, 5.0f * side, 0.0f, 5.0f);
	cylinder = Cylinder(pObj, cylinder.getTop(), cylinder.getTop() / 2.0, cylinder.getHeight() / 3.0, 26, 13, rotation, position, color);
	cylinder.draw();

	rotation.setAngle(60 * side);
	cylinder.setRotation(rotation);
	cylinder.draw();
}

// Called to draw scene
void drawScene(void) {
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	// floor
	color = Color(0xFFFFFF);
	position = Position(0.0, -floorHeight, 0.0);
	rotation = Rotation(-90.0f, 1.0f, 0.0f, 0.0f);
	disk = Disk(pObj, 0.0, floorRadius, 1000, 10, rotation, position, color);
	disk.draw();
	rotation.setAngle(90.0f);
	disk.setRotation(rotation);
	disk.draw();

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

	position.setY(-globeOpeningHeight);
	disk.setOuter(sqrt((pow(globeRadius, 2) - pow(globeOpeningHeight, 2))));
	disk.setPosition(position);
	disk.draw();

	// snowman's feet
	position.setY(-floorHeight + (feetRadius * 0.9));
	sphere = Sphere(pObj, feetRadius, 104, 52, rotation, position, color);
	sphere.draw();

	// snowman's body
	position.setY(bodyY);
	sphere = Sphere(pObj, bodyRadius, 104, 52, rotation, position, color);
	sphere.draw();

	// snowman's head
	position.setY(headY);
	sphere = Sphere(pObj, headRadius, 104, 52, rotation, position, color);
	sphere.draw();

	position.setY(position.getY() + headRadius);

	// snowman's bucket
	position.setY(position.getY() + (bucketHeight / 3.0));
	color = Color(0x261614);
	cylinder = Cylinder(pObj, headRadius * 0.95f, headRadius * 1.05f, bucketHeight, 50, 150, rotation, position, color);
	position.setY(position.getY() * 0.95);
	cylinder.setPosition(position);
	cylinder.draw();

	rotation.setAngle(-90);
	// bucket's top
	disk = Disk(pObj, 0, cylinder.getBase(), 104, 52, rotation, position, color);
	disk.draw();

	// bucket's brim
	cylinder.setRotation(rotation);
	cylinder.setBase(cylinder.getBase() * 1.3);
	position.setY(position.getY() - cylinder.getHeight() * 1.5);
	cylinder.setHeight(cylinder.getHeight() * 0.5);
	color = Color(0x211412);
	cylinder.setPosition(position);
	cylinder.draw();

	// eyes
	// right
	color = Color(0x000000);
	position = Position((0.5 * glassMult) - (eyeSize / 2.0), (headY * (3 / 4.0)) + (0.375 * glassMult) + (eyeSize / 2.0), headRadius - eyeSize);
	sphere = Sphere(pObj, headRadius * 0.1, 26, 13, rotation, position, color);
	sphere.draw();

	// left
	position.setX(position.getX() * -1);
	sphere.setPosition(position);
	sphere.draw();

	// earrings
	// right
	color = Color(0xEDC967);
	sphere.setColor(color);
	position.setX(headRadius);
	position.setY(position.getY() - sphere.getSize());
	position.setZ(0);
	sphere.setPosition(position);
	sphere.draw();

	// left
	position.setX(position.getX() * -1);
	sphere.setPosition(position);
	sphere.draw();

	float yIntersection = calculateYAxisOfIntersection(bodyRadius, headRadius, bodyY, headY);
	float xIntersection = calculateXAxisOfIntersection(bodyRadius, yIntersection, bodyY);

	Position necklaceStart = Position(xIntersection + sphere.getSize(), yIntersection, 0);
	position = necklaceStart;
	sphere.setPosition(position);
	sphere.draw();
	necklaceStart.setX(necklaceStart.getX() * -1);
	sphere.setPosition(necklaceStart);
	sphere.draw();
	necklaceStart.setX(necklaceStart.getX() * -1);

	position.setX(position.getX() - sphere.getSize() / 2);
	position.setZ(position.getZ() - sphere.getSize() * 2);
	sphere.setPosition(position);
	sphere.draw();
	position.setX(position.getX() * -1);
	sphere.setPosition(position);
	sphere.draw();

	position = necklaceStart;
	for (int i = 0; i < 20; i++) {
		position.setX(position.getX() - sphere.getSize());
		position.setZ(-generateAnotherCoordinateOnSurface(headRadius + (sphere.getSize()), headY, position.getX(), position.getY(), Z));
		sphere.setPosition(position);
		sphere.draw();
	}

	Position neckLaceLeft = necklaceStart;
	Position neckLaceRight = Position(-neckLaceLeft.getX(), neckLaceLeft.getY(), neckLaceLeft.getZ());
	// necklace
	for (int i = 0; i < 9; i++) {
		neckLaceLeft.setZ(neckLaceLeft.getZ() + sphere.getSize() * 1.25);
		neckLaceLeft.setY(neckLaceLeft.getY() - sphere.getSize() * 0.5);
		neckLaceLeft.setX(generateAnotherCoordinateOnSurface(bodyRadius + (sphere.getSize() * 0.5), bodyY, neckLaceLeft.getY(), neckLaceLeft.getZ(), X));
		sphere.setPosition(neckLaceLeft);
		sphere.draw();
		neckLaceRight = Position(-neckLaceLeft.getX(), neckLaceLeft.getY(), neckLaceLeft.getZ());
		sphere.setPosition(neckLaceRight);
		sphere.draw();
	}

	// Draw the sunglasses
	glPushMatrix();
		color = Color(0x601A16);
		glTranslatef(0, headY * (3 / 4.0), headRadius);
		// set the color to black
		glColor3f(color.getRed(), color.getGreen(), color.getBlue());
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
			color = Color(0x76655A);
			glColor3f(color.getRed(), color.getGreen(), color.getBlue());
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
	color = Color(0xED9121);
	rotation.setAngle(0);
	position = Position(0.0f, headY * 0.975, headRadius);
	cylinder = Cylinder(pObj, headRadius * 0.1, 0.0f, headRadius * 0.8, 26, 13, rotation, position, color);
	cylinder.draw();

	drawArm(bodyRadius, bodyY, pObj, RIGHT);
	drawArm(bodyRadius, bodyY, pObj, LEFT);

	// floor
	color = Color(0xC54245);
	rotation = Rotation(90.0f, 1.0f, 0.0f, 0.0f);
	position = Position(0.0f, -globeOpeningHeight, 0.0f);
	cylinder = Cylinder(pObj, globeOpeningRadius, globeOpeningRadius * 1.15, floorHeight * 1.1, 50, 150, rotation, position, color);
	cylinder.draw();

	position.setY(position.getY() - cylinder.getHeight());
	disk = Disk(pObj, 0.0, cylinder.getTop(), 1000, 10, rotation, position, color);
	disk.draw();

	// glPushMatrix();
	// 	moveParticles(pObj, snow, NUM_OF_PARTICLES, floorRadius, -floorHeight);
	// glPopMatrix();

	// draw the translucent sphere
	glPushMatrix();
		glClipPlane(GL_CLIP_PLANE0, bottomPlane);
		glEnable(GL_CLIP_PLANE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		color = Color(0x0c1445);
		glColor4f(color.getRed(), color.getGreen(), color.getBlue(), 0.2);
		gluQuadricDrawStyle(pObj, GLU_FILL);
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluSphere(pObj, globeRadius, 104, 52);
		gluDeleteQuadric(pObj);
		glDisable(GL_BLEND);
		glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}

int main(int argc, char *argv[]) {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Snow G-Loc");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	setupRC();
	// generateParticles(snow, NUM_OF_PARTICLES, globeRadius, -floorHeight);
	glutMainLoop();

	return 0;
}
