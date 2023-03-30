#include "CApp.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BIT_DEPTH 24

int main(int argc, char* argv[]) {
	argc--, argv--;
	CApp cApp = CApp(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_DEPTH);

	return cApp.OnExecute();
}
