#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "utils.h"

#define NUM_OF_PARTICLES 3000
#define LIFETIME 100

typedef struct Particle {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat xVelocity;
	GLfloat yVelocity;
	GLfloat zVelocity;

	unsigned int lifetime;
} Particle;

void generateParticles();
void regenerateParticle(int index);
void moveParticles();

#endif
