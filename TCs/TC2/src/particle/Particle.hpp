#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include "Color.hpp"

class Particle {
	public:
		Particle(float x, float y, float velocityX, float velocityY, float size, unsigned int lifeTime, Color color);

	private:
		float x;
		float y;
		float velocityX;
		float velocityY;
		float size;
		unsigned int lifeTime;
		Color color;
};

#endif
