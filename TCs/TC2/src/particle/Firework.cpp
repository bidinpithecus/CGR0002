#include "Firework.hpp"

Firework::Firework() {
}

Firework::Firework(int numParticles, double gravity) {
	this->numParticles = numParticles;
	this->gravity = gravity;
	this->initFirework();
}

void Firework::DisplayCallback() {
    fireworkInstance->DrawGLScene();
}

void Firework::initFirework() {
	float velocity;
	float velX;
	float velY;
	int angle;
	unsigned int lifeTime;

	for (int i = 0; i < this->numParticles; i++) {
		angle = randomNum(360);
		velocity = randomNum(100) / 5000.0;
		velX = cos(M_PI * angle / 180.0) * velocity;
		velY = sin(M_PI * angle / 180.0) * velocity;
		lifeTime = randomNum(100);

		Particle particle = Particle(0.0, 0.0, velX, velY, 0.1, lifeTime, *(new Color(0xFFFFFF)));
		this->fireworks.push_back(particle);
	}
}

void Firework::DrawGLScene(GLvoid) {
	int activeParticles = 0;

    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity();
	glTranslatef(0.0f,0.0f,-6.0f);		// Move particles 6.0 units into the screen

	glBegin(GL_POINTS);

	for(int i = 0; i < this->numParticles; i++) {
		if(fireworks[i].isParticleAlive()) {
			Particle particle = fireworks[i];
			activeParticles++;
			particle.setVelocityY(particle.getVelocityY() - this->gravity);
			particle.setX(particle.getX() + particle.getVelocityX());
			particle.setY(particle.getY() + particle.getVelocityY());
			particle.setLifeTime(particle.getLifeTime() - 1);

			glVertex3f( particle.getX(), particle.getY(), 0.0f); // draw pixel
		}
	}
	glEnd();

	usleep(20000);
}

int Firework::getNumParticles() {
	return this->numParticles;
}
