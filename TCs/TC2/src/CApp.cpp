#include "CApp.hpp"

// Default constructor
CApp::CApp() {
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
}

bool CApp::OnInit(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	pWindow = SDL_CreateWindow("Particles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (pWindow != NULL) {
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	} else {
		return false;
	}

	return true;
}

int CApp::OnExecute() {
	int width = 640;
	int height = 480;
	SDL_Event event;
	if (!OnInit(width, height)) {
		return -1;
	}

	while(isRunning) {
		while(SDL_PollEvent(&event)) {
			OnEvent(&event);
		}

		OnLoop();
		OnRender();
	}

	OnExit();
	return 0;
}

void CApp::OnEvent(SDL_Event* event) {
	if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
	}
	if (event->type == SDL_QUIT) {
		isRunning = false;
	}
}

void CApp::OnLoop() {

}

void CApp::OnRender() {
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	SDL_RenderPresent(pRenderer);
}

void CApp::OnExit() {
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}
