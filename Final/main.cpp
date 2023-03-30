#include "CApp.hpp"

int main(int argc, char* argv[]) {
	argc--, argv--;
	CApp cApp = CApp(640, 480);

	return cApp.OnExecute();
}
