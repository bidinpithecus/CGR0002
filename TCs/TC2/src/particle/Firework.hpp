#ifndef _FIREWORK_HPP_
#define _FIREWORK_HPP_

#include "Particle.hpp"
#include "Random.hpp"
#include <vector>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <unistd.h>

class Firework {
	public:
		Firework();
		Firework(int numParticles, double gravity);
		void initFirework();
		void DrawGLScene(GLvoid);
		int getNumParticles();
		static void DisplayCallback();

	private:
		static Firework* fireworkInstance; // static pointer to instance of Firework class
		int numParticles;
		std::vector<Particle> fireworks;
		double gravity;
};

#endif
