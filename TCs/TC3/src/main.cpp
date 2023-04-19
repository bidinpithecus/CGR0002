#include "main.hpp"
#include "Boid.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include <GL/glu.h>

Color color;

Cylinder cylinder;
Disk disk;
Sphere sphere;
Cube cube;

Position position;
Scale scale;
Rotation rotation;

Scale floorScale = Scale(10, 1, 10);
Position floorPosition = Position(0, 0, 0);

GLUquadricObj* pMoon;

std::vector<Boid> swarm;

const GLfloat moonRadius = 5;
const int numOfBoids = 50;

void drawMoon() {
	pMoon = gluNewQuadric();
	gluQuadricNormals(pMoon, GLU_SMOOTH);

    // Set up moonlight properties
    GLfloat moonPosition[] = {-10.f, 5.0f, 5.0f, 1.0f};
    GLfloat moonDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonEmission[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat moonConstantAttenuation = 1.0f; // Constant attenuation factor
    GLfloat moonLinearAttenuation = 0.0f; // Linear attenuation factor
    GLfloat moonQuadraticAttenuation = 0.01f; // Quadratic attenuation factor, adjust as needed

    glPushMatrix();
		glTranslatef(moonPosition[0], moonPosition[1], moonPosition[2]);
		glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, moonDiffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, moonSpecular);
		glLightfv(GL_LIGHT1, GL_EMISSION, moonEmission);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, moonConstantAttenuation);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, moonLinearAttenuation);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, moonQuadraticAttenuation);
		glColor3f(1.0, 1.0, 1.0);
		gluSphere(pMoon, 0.1f, 30, 17);
    glPopMatrix();
}

void drawFlocks(int limitX, int limitY, int limitZ) {
	for (Boid boid : swarm) {
		calculateNeighbors(&swarm, 1);
		boid.edges(limitX, limitY, limitZ);
		boid.applyBehaviour();
		boid.update();
		boid.show();
	}
}

// Called to draw scene
void drawScene(void) {
	drawMoon();
	// draw earth
	rotation = Rotation(0, 0, 0, 0);
	cube = Cube(1, rotation, floorPosition, floorScale, Color(0x5A3E33));
	cube.draw();

	// draw grass
	scale = floorScale;
	scale.setY(floorScale.getY() * 0.1);
	position = floorPosition;
	position.setY(floorScale.getY() / 2.0 + scale.getY() / 2.0);
	cube.setPosition(position);
	cube.setScale(scale);
	cube.setColor(Color(0x0B3405));
	cube.draw();

	drawFlocks(15, 10, 15);
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < numOfBoids; i++) {
		swarm.push_back(Boid());
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Part 3");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	setupRC();
	glutMainLoop();

	return 0;
}
