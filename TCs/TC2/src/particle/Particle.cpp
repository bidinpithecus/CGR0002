#include "Particle.hpp"

Particle::Particle(float x, float y, float velocityX, float velocityY, float size, unsigned int lifeTime, Color color) {
	this->x = x;
	this->y = y;
	this->velocityX = velocityX;
	this->velocityY = velocityY;
	this->size = size;
	this->lifeTime = lifeTime;
	this->color = color;
}

bool Particle::isParticleAlive() {
	return this->lifeTime != 0;
}

void Particle::setX(float x) {
	this->x = x;
}

void Particle::setY(float y) {
	this->y = y;
}

void Particle::setVelocityX(float velocityX) {
	this->velocityX= velocityX;
}

void Particle::setVelocityY(float velocityY) {
	this->velocityY= velocityY;
}

void Particle::setLifeTime(unsigned int lifeTime) {
	this->lifeTime = lifeTime;
}

void Particle::setColor(Color color) {
	this->color = color;
}

float Particle::getX() {
	return this->x;
}

float Particle::getY() {
	return this->y;
}

float Particle::getVelocityX() {
	return this->velocityX;
}

float Particle::getVelocityY() {
	return this->velocityY;
}

unsigned int Particle::getLifeTime() {
	return this->lifeTime;
}

Color Particle::getColor() {
	return this->color;
}
