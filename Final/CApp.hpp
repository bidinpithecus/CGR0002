#ifndef _C_APP_HPP_
#define _C_APP_HPP_

#include "rayTracing/Image.hpp"

class CApp {
	public:
		CApp(int width, int height);
		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnExit();

	private:
		Image image;
		int width;
		int height;

		bool isRunning;
		SDL_GLContext glContext;
		SDL_Renderer* pRenderer;
		SDL_Window* pWindow;

};

#endif
