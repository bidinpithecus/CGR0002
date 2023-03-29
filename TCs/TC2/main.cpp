#include "CApp.hpp"

int main(int argc, char* argv[]) {
	argc--, argv--;
	CApp cApp;

	return cApp.OnExecute();
}
