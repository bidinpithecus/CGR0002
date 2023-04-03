#ifndef _FIREWORK_HPP_
#define _FIREWORK_HPP_

#include "Particle.hpp"

class Firework:public Particle {
	public:
		Firework(int numParticles, double gravity);
		void initParticle();

	private:
		int numParticles;
		double gravity;
};

#endif
