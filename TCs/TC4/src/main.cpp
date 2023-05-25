#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate3D.hpp"
#include "Coordinate2D.hpp"
#include "Helpers.hpp"
#include <GL/gl.h>
#include <ctime>
#include <vector>

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float fps = 0.0;

GLUquadricObj *pObj;

void idle(void) {
	getFps();
	glutPostRedisplay();
}

void drawScene() {

}

int main(int argc, char **argv) {
    srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Obstacle Avoidance");
	glutReshapeFunc(resize);
	glutKeyboardFunc(normalKeyPressed);
	glutSpecialFunc(specialKeyPressed);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	setupRC();
	glutMainLoop();

	return 0;
}
