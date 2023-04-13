#include "main.hpp"
#include "Color.hpp"
#include "Shapes.hpp"

Color color;

Cylinder cylinder;
Disk disk;
Sphere sphere;

Position position;
Rotation rotation;

// Called to draw scene
void drawScene(void) {}

int main(int argc, char *argv[]) {
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
