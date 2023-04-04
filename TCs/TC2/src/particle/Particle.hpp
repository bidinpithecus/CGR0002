#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include "Color.hpp"

class Particle {
	public:
		Particle(float x, float y, float velocityX, float velocityY, float size, unsigned int lifeTime, Color color);
		bool isParticleAlive();
		void setX(float x);
		void setY(float y);
		void setVelocityX(float velocityX);
		void setVelocityY(float velocityY);
		void setLifeTime(unsigned int lifeTime);
		void setColor(Color color);

		float getX();
		float getY();
		float getVelocityX();
		float getVelocityY();
		unsigned int getLifeTime();
		Color getColor();

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
