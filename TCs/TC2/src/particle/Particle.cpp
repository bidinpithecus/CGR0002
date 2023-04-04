#include "Particle.hpp"

Particle::Particle(float x, float y, float velocityX, float velocityY, float size, unsigned int lifeTime, Color color) {
	this->x = x;
	this->y = y;
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	this->lifeTime = lifeTime;
	this->color = color;
}
