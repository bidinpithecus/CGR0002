#include "main.hpp"
#include "Boid.hpp"
#include "Color.hpp"
#include "Shapes.hpp"
#include <cmath>
#include <unistd.h>

Color color;

Cylinder cylinder;
Disk disk;
Sphere sphere;
Cube cube;

Position position;
Scale scale;
Rotation rotation;

const Position floorPosition = Position(0, 0, 0);
const int floorSide = 10;
Scale floorScale = Scale(floorSide, floorSide * 0.1, floorSide);
const GLfloat moonRadius = 10;
const int numOfBoids = 350;
float grassY = floorScale.getY() / 2.0 + (floorScale.getY() * 0.1) / 2.0;

GLUquadricObj* pMoon;

std::vector<Boid> swarm;

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

void drawFlocks(Position lowerLimit, Position upperLimit) {
	calculateNeighbors(swarm, 0.175);

	for (auto& boid : swarm) {
		boid.applyBehaviour(5, 0.01, 100);
		boid.edges(lowerLimit, upperLimit);
		boid.update();
		boid.show(randomFloat(0.025, 0.035), Color(0x000000));
	}
}

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
	position.setY(grassY);
	cube.setPosition(position);
	cube.setScale(scale);
	cube.setColor(Color(0x0B3405));
	cube.draw();

	drawFlocks(Position(-floorSide / 2.0, grassY * 15, -floorSide / 2.0), Position(floorSide / 2.0, floorSide, floorSide / 2.0));
}

int main(int argc, char *argv[]) {
	srand(time(0));
	for (int i = 0; i < numOfBoids; i++) {
		swarm.push_back(Boid(Position(-floorSide / 2.0, grassY * 15, -floorSide / 2.0), Position(floorSide / 2.0, floorSide, floorSide / 2.0)));
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
