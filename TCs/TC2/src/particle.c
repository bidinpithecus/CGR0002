#include "particle.h"

Particle snow[NUM_OF_PARTICLES];
GLfloat snowSize = 5.0;

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY) {
	for (int i = 0; i < numOfParticles; i++) {
		particles[i].x = randomFloat(-radius, radius);
		particles[i].y = initialY;
		particles[i].z = generateCoordinateInsideSphere(radius, particles[i].x, particles[i].y);

		particles[i].xVelocity = 0.001;
		particles[i].yVelocity = 0.020;
		particles[i].zVelocity = 0.001;

		particles[i].lifetime = LIFETIME;
	}
}

void regenerateParticle(Particle* particles, int index, GLfloat radius, GLfloat initialY) {
	particles[index].x = randomFloat(-radius, radius);
	particles[index].y = initialY;
	particles[index].z = generateCoordinateInsideSphere(radius, particles[index].x, particles[index].y);

	particles[index].xVelocity = 0.001;
	particles[index].yVelocity = 0.05;
	particles[index].zVelocity = 0.001;

	particles[index].lifetime = LIFETIME;
}

void moveParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground) {
	glPointSize(snowSize);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < numOfParticles; i++) {
		if (particles[i].y >= ground) {
			printf("snow %d falling\n", i);
			particles[i].y -= particles[i].yVelocity;

		} else {
			printf("snow %d hit the ground\n", i);
			particles[i].y = generateAnotherCoordinateOnSurface(radius, particles[i].x, particles[i].z);
		}

		glVertex3f(particles[i].x, particles[i].y, particles[i].z);
		// printf("height of particle %d: %lf\n", i, particles[i].y);
	}
	glEnd();
}
