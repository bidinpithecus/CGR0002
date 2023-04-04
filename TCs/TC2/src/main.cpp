#include "CApp.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BIT_DEPTH 24
#define NUM_PARTICLES 3000
#define GRAVITY 0.0003

Firework* Firework::fireworkInstance = new Firework();
CApp* CApp::cAppInstance = new CApp();

int main(int argc, char* argv[]) {
	argc--, argv--;
	glutInit(&argc, argv);

	CApp cApp = CApp(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_DEPTH, NUM_PARTICLES, GRAVITY);

	return cApp.OnExecute();
}
