#include "CApp.hpp"

// Default constructor
CApp::CApp(int width, int height) {
	this->width = width;
	this->height = height;

	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
	glContext = NULL;
}

bool CApp::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	pWindow = SDL_CreateWindow("Particles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (pWindow != NULL) {
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		glContext = SDL_GL_CreateContext(pWindow);
		image.Initialize(width, height, pRenderer);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double red = (static_cast<double>(x) / width) * 255.0;
				double green = (static_cast<double>(y) / height) * 255.0;

				image.setPixel(x, y, red, green, 0.0);
			}
		}

	} else {
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
	if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
		width = event->window.data1;
		height = event->window.data2;

		image.UpdateSize(width, height);
		std::cout << "(" << event->window.data1 << ", " << event->window.data2 << ")" << std::endl;
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
	image.Initialize(width, height, pRenderer);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			double red = (static_cast<double>(x) / width) * 255.0;
			double green = (static_cast<double>(y) / height) * 255.0;

			image.setPixel(x, y, red, green, 0.0);
		}
	}

	image.Display();

	SDL_RenderPresent(pRenderer);
}

void CApp::OnExit() {
	SDL_DestroyRenderer(pRenderer);
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}
