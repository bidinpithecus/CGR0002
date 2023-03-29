#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL2/SDL.h>

class CApp {
	public:
		CApp();
		int OnExecute();
		bool OnInit(int width, int height);
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnExit();

	private:
		bool isRunning;
		SDL_GLContext glContext;
		SDL_Renderer* pRenderer;
		SDL_Window* pWindow;

};

#endif
