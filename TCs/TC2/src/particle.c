#include "particle.h"

Particle snow[NUM_OF_PARTICLES];

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY) {
	for (int i = 0; i < numOfParticles; i++) {
		(&particles[i])->x = randomNum(-radius, radius);
		(&particles[i])->y = initialY;
		(&particles[i])->z = generateCoordinateInsideSphere(radius, (&particles[i])->x, (&particles[i])->y);

		(&particles[i])->xVelocity = 0;
		(&particles[i])->yVelocity = 0.1f;
		(&particles[i])->zVelocity = 0;

		(&particles[i])->lifetime = LIFETIME;
	}
}

void regenerateParticle(Particle* particles, int index, GLfloat radius, GLfloat initialY) {
	(&particles[index])->x = randomNum(-radius, radius);
	(&particles[index])->y = initialY;
	(&particles[index])->z = generateCoordinateInsideSphere(radius, (&particles[index])->x, (&particles[index])->y);

	(&particles[index])->xVelocity = 0;
	(&particles[index])->yVelocity = 0.1f;
	(&particles[index])->zVelocity = 0;

	(&particles[index])->lifetime = LIFETIME;
}

void printParticles(Particle* particles, int numOfParticles) {
	for (int i = 0; i < numOfParticles; i++) {
		printf("(%lf, %lf, %lf); (%lf, %lf, %lf); (%d)\n", particles[i].x, particles[i].y, particles[i].z, particles[i].xVelocity, particles[i].yVelocity, particles[i].zVelocity, particles[i].lifetime);
	}
}

void moveParticles(Particle* particles, int numOfParticles, GLfloat ground) {
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < numOfParticles; i++) {
		if ((&particles[i])->y > ground) {
			// snow falling
			(&particles[i])->x += (&particles[i])->xVelocity;
			(&particles[i])->y += (&particles[i])->yVelocity;
			(&particles[i])->z += (&particles[i])->zVelocity;

		} else {
			(&particles[i])->xVelocity = 0;
			(&particles[i])->yVelocity = 0;
			(&particles[i])->zVelocity = 0;
			(&particles[i])->y = ground;
		}

		glVertex3f((&particles[i])->x, (&particles[i])->y, (&particles[i])->z);
	}
	glEnd();
}
