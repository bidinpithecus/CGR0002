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
	particle->yVelocity = GRAVITY * randomFloat(1, 10);
	particle->zVelocity = 0.0;

	particle->size = randomFloat(radius * 0.001f, radius * 0.006);
	particle->lifetime = LIFETIME;
}

void moveParticles(GLUquadric* quad, Particle* particles, int numOfParticles, GLfloat floorRadius, GLfloat ground) {
	Sphere snowflake = newSphere(quad, 0.0, 104, 52);
	Position snowPos;
	int color = 0xFFFFFF;

	for (int i = 0; i < numOfParticles; i++) {
		if (particles[i].y >= ground) {
			particles[i].yVelocity += GRAVITY;
			particles[i].y -= particles[i].yVelocity;
		} else {
			floorRadius -= particles[i].size;
			particles[i].x = randomFloat(-floorRadius, floorRadius);
			particles[i].z = randomFloat(-floorRadius, floorRadius);
			particles[i].y = generateAnotherCoordinateOnSurface(floorRadius, particles[i].x, particles[i].z);
			particles[i].yVelocity = GRAVITY;
		}

		snowflake.radius = particles[i].size;
		snowPos = newPosition(particles[i].x, particles[i].y, particles[i].z);
		drawSphere(color * (particles[i].lifetime / LIFETIME), snowflake, snowPos);
	}
}
