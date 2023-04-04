#include "Firework.hpp"

Firework::Firework(int numParticles, double gravity) {
	this->numParticles = numParticles;
	this->gravity = gravity;
}

void Firework::initFirework() {
	float velocity;
	int angle;

	for (int i = 0; i < this->numParticles; i++) {
		Particle* particle = new Particle(0.0, 0.0, std::cos(M_PI), sin(M_PI), 0.1, 10, Color(0xFFFFFF));
		this->fireworks.push_back(*particle);
	}
}
