#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "utils.h"

#define NUM_OF_PARTICLES 500
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

extern Particle snow[NUM_OF_PARTICLES];
extern GLfloat snowSize;

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY);
void regenerateParticle(Particle* particles, int index, GLfloat radius, GLfloat initialY);
void moveParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground);
void printParticles(Particle* particles, int numOfParticles);

#endif
