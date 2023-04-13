#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "utils.h"

#define NUM_OF_PARTICLES 500
#define LIFETIME 100
#define GRAVITY 0.001

typedef struct Particle {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat xVelocity;
	GLfloat yVelocity;
	GLfloat zVelocity;

	GLfloat size;
	unsigned int lifetime;
} Particle;

extern Particle snow[NUM_OF_PARTICLES];

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY);
void generateParticle(Particle* particle, GLfloat radius, GLfloat initialY);
void moveParticles(GLUquadric* quad, Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground);
void printParticles(Particle* particles, int numOfParticles);

#endif
