#ifndef _FIREWORK_HPP_
#define _FIREWORK_HPP_

#include "Particle.hpp"
#include <vector>
#include <math.h>

class Firework {
	public:
		Firework(int numParticles, double gravity);
		void initFirework();

	private:
		int numParticles;
		std::vector<Particle> fireworks;
		double gravity;
};

#endif
