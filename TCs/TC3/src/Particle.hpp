#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include <stdio.h>
#include "Utils.hpp"
#include "Helpers.hpp"

#define NUM_OF_PARTICLES 500
#define LIFETIME 100
#define GRAVITY 0.001

class Particle {
	public:
		Particle();
		Particle(Position position, Position velocity, GLfloat size, unsigned int lifetime);
		void setPosition(Position position);
		void setVelocity(Position position);
		void setSize(GLfloat size);
		void setLifetime(unsigned int lifetime);

		Position getPosition();
		Position getVelocity();
		GLfloat getSize();
		unsigned int getLifetime();

		void printInfo();
		void generate(GLfloat biggerRadius, GLfloat initialY);
		void move(GLfloat floorRadius, GLfloat ground);

	private:
		Position position;
		Position velocity;
		GLfloat size;
		unsigned int lifetime;
};

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY);
void moveParticles(GLUquadric* quad, Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground);

#endif
