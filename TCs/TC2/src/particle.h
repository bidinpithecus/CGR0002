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

extern Particle particles[NUM_OF_PARTICLES];

extern GLfloat initX;
extern GLfloat initY;
extern GLfloat initZ;
extern GLfloat ground;

void generateParticles(Particle* particles, int numOfParticles);
void regenerateParticle(Particle* particles, int index);
void moveParticles(Particle* particles, int numOfParticles);
void printParticles(Particle* particles, int numOfParticles);

#endif
