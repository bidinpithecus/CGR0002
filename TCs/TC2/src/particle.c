#include "particle.h"

Particle particles[NUM_OF_PARTICLES];

GLfloat initX = 0;
GLfloat initY = 0;
GLfloat initZ = 0;
GLfloat ground = 0;

void generateParticles(Particle* particles, int numOfParticles) {
	for (int i = 0; i < numOfParticles; i++) {
		(&particles[i])->x = initX;
		(&particles[i])->y = initY;
		(&particles[i])->z = initZ;

		(&particles[i])->xVelocity = 0;
		(&particles[i])->yVelocity = 0.1f;
		(&particles[i])->zVelocity = 0;

		(&particles[i])->lifetime = LIFETIME;
	}
}

void regenerateParticle(Particle* particles, int index) {
	(&particles[index])->x = initX;
	(&particles[index])->y = initY;
	(&particles[index])->z = initZ;

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

void moveParticles(Particle* particles, int numOfParticles) {
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
