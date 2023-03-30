#ifndef _C_APP_HPP_
#define _C_APP_HPP_

#include <SDL2/SDL.h>
#include <iostream>
#include "../include/glad.h"

class CApp {
	public:
		CApp(int width, int height, int bitDepth);
		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnExit();
		void getOpenGLInfo();

	private:
		int width;
		int height;
		int bitDepth;

		bool isRunning;
		SDL_GLContext glContext;
		SDL_Renderer* pRenderer;
		SDL_Window* pWindow;
};

#endif
