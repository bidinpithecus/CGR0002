#include "particle.h"

Particle snow[NUM_OF_PARTICLES];

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY) {
	for (int i = 0; i < numOfParticles; i++) {
		generateParticle(&particles[i], radius, initialY);
	}
}

void generateParticle(Particle* particle, GLfloat radius, GLfloat initialY) {
	particle->x = randomFloat(-radius, radius);
	particle->y = initialY;
	particle->z = generateCoordinateInsideSphere(radius, particle->x, particle->y);

	particle->xVelocity = 0.0;
	particle->yVelocity = 0.01;
	particle->zVelocity = 0.0;

	particle->size = randomFloat(radius * 0.001f, radius * 0.006);
}

void moveParticles(GLUquadric* quad, Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground) {
	Sphere snowflake = newSphere(quad, 0.0, 104, 52);
	Position snowPos;
	int color = 0xFFFFFF;

	for (int i = 0; i < numOfParticles; i++) {
		if (particles[i].y >= ground) {
			particles[i].y -= particles[i].yVelocity;
		} else {
			radius -= particles[i].size;
			particles[i].x = randomFloat(-radius, radius);
			particles[i].z = randomFloat(-radius, radius);
			particles[i].y = generateAnotherCoordinateOnSurface(radius, particles[i].x, particles[i].z);
		}

		snowflake.radius = particles[i].size;
		snowPos = newPosition(particles[i].x, particles[i].y, particles[i].z);
		drawSphere(color, snowflake, snowPos);
	}
}
