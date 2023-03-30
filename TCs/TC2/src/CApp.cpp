#include "CApp.hpp"
#include <SDL2/SDL_video.h>

// Default constructor
CApp::CApp(int width, int height, int bitDepth) {
	this->width = width;
	this->height = height;
	this->bitDepth = bitDepth;

	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
	glContext = NULL;
}

void CApp::getOpenGLInfo() {
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

bool CApp::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Unable to initiate SDL" << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bitDepth);

	pWindow = SDL_CreateWindow("Particles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (pWindow != NULL) {
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	} else {
		std::cerr << "Unable to create window" << std::endl;
		return false;
	}

	glContext = SDL_GL_CreateContext(pWindow);
	if (glContext == NULL) {
		std::cerr << "Unable to create context" << std::endl;
		return false;
	}

	if (gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		getOpenGLInfo();
	} else {
		std::cerr << "Unable to load glad" << std::endl;
		return false;
	}

	return true;
}

int CApp::OnExecute() {
	SDL_Event event;
	if (!OnInit()) {
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
