#include "particle.h"

Particle snow[NUM_OF_PARTICLES];
GLfloat snowSize = 5.0;

void generateParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat initialY) {
	radius -= (snowSize * 0.05f);
	for (int i = 0; i < numOfParticles; i++) {
		(&particles[i])->x = randomFloat(-radius, radius);
		(&particles[i])->y = initialY;
		(&particles[i])->z = generateCoordinateInsideSphere(radius, snowSize, (&particles[i])->x, (&particles[i])->y);

		(&particles[i])->xVelocity = 0;
		(&particles[i])->yVelocity = 0.1f;
		(&particles[i])->zVelocity = 0;

		(&particles[i])->lifetime = LIFETIME;
	}
}

void regenerateParticle(Particle* particles, int index, GLfloat radius, GLfloat initialY) {
	radius -= (snowSize * 0.1f);
	(&particles[index])->x = randomFloat(-radius, radius);
	(&particles[index])->y = initialY;
	(&particles[index])->z = generateCoordinateInsideSphere(radius, snowSize, (&particles[index])->x, (&particles[index])->y);

	(&particles[index])->xVelocity = 0;
	(&particles[index])->yVelocity = 1;
	(&particles[index])->zVelocity = 0;

	(&particles[index])->lifetime = LIFETIME;
}

void printParticles(Particle* particles, int numOfParticles) {
	for (int i = 0; i < numOfParticles; i++) {
		printf("(%lf, %lf, %lf); (%lf, %lf, %lf); (%d)\n", particles[i].x, particles[i].y, particles[i].z, particles[i].xVelocity, particles[i].yVelocity, particles[i].zVelocity, particles[i].lifetime);
	}
}

void moveParticles(Particle* particles, int numOfParticles, GLfloat radius, GLfloat ground) {
	radius -= snowSize;
	glPointSize(snowSize);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < numOfParticles; i++) {
		if ((&particles[i])->y > ground) {
			printf("snow %d falling\n", i);
			// snow falling
			(&particles[i])->x += (&particles[i])->xVelocity;
			(&particles[i])->y -= (&particles[i])->yVelocity;
			(&particles[i])->z += (&particles[i])->zVelocity;

		} else {
			printf("snow %d hit the ground\n", i);
			(&particles[i])->xVelocity = 0;
			(&particles[i])->yVelocity = 0;
			(&particles[i])->zVelocity = 0;
			(&particles[i])->y = generateAnotherCoordinateOnSurface(radius, (&particles[i])->x, (&particles[i])->z);
		}

		glVertex3f((&particles[i])->x, (&particles[i])->y, (&particles[i])->z);
		printf("height of particle %d: %lf\n", i, particles[i].y);
	}
	glEnd();
}
