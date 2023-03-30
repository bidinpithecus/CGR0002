#include "CApp.hpp"

int main(int argc, char* argv[]) {
	argc--, argv--;
	CApp cApp = CApp(1280, 720);

	return cApp.OnExecute();
}
