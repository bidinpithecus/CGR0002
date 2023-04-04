#ifndef _C_APP_HPP_
#define _C_APP_HPP_

#include <GL/glut.h>  // Header File For The GLUT Library
#include <GL/gl.h>	  // Header File For The OpenGL32 Library
#include <GL/glu.h>	  // Header File For The GLu32 Library
#include <iostream>
#include "particle/Firework.hpp"

class CApp {
	public:
		CApp();
		CApp(int width, int height, int bitDepth, int numParticles, double gravity);
		static void ResizeCallback(int width, int height);
		static void NormalKeyCallback(unsigned char key, int x, int y);
		static void SpecialKeyCallback(int key, int x, int y);
		void OnNormalKeyPressed(unsigned char key, int x, int y);
		void OnSpecialKeyPressed(int key, int x, int y);

		int OnExecute();
		void Setup();
		bool OnInit();
		void OnLoop();
		void OnRender();
		void OnResize(int width, int height);
		void OnExit();
		void getOpenGLInfo();

	private:
		int width;
		int height;
		int bitDepth;
		Firework firework;
		static CApp* cAppInstance; // static pointer to instance of CApp class

		bool isRunning;
		int window;
};

#endif
