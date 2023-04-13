#include "Particle.hpp"

Particle::Particle() {}

Particle::Particle(Position position, Position velocity, GLfloat size, unsigned int lifetime) {
	this->position = position;
	this->velocity = velocity;
	this->size = size;
	this->lifetime = lifetime;
}

Position Particle::getPosition() {
	return this->position;
}

Position Particle::getVelocity() {
	return this->velocity;
}

GLfloat Particle::getSize() {
	return this->size;
}

unsigned int Particle::getLifetime() {
	return this->lifetime;
}

void Particle::setPosition(Position position) {
	this->position = position;
}

void Particle::setVelocity(Position velocity) {
	this->velocity = velocity;
}

void Particle::setSize(GLfloat size) {
	this->size = size;
}

void Particle::setLifetime(unsigned int lifetime) {
	this->lifetime = lifetime;
}

void Particle::printInfo() {
	printf("pos(%lf, %lf, %lf)\t vel(%lf, %lf, %lf)\n", this->getPosition().getX(), this->getPosition().getY(), this->getPosition().getZ(), this->getVelocity().getX(), this->getVelocity().getY(), this->getVelocity().getZ());
}

void Particle::generate(GLfloat floorRadius, GLfloat biggerRadius) {
	Position position = Position();
	this->setSize(randomFloat(biggerRadius * 0.001f, biggerRadius * 0.0025));
	biggerRadius -= this->getSize();
	floorRadius -= this->getSize();
	position.setX(randomFloat(-biggerRadius, biggerRadius));
	position.setZ(randomFloat(-biggerRadius, biggerRadius));
	position.setY(generateAnotherCoordinateOnSurface(floorRadius, 0, position.getX(), position.getZ(), Y));
	position.setY(position.getY() + (biggerRadius - floorRadius));
	this->setPosition(position);
	this->setVelocity(Position(0.0, GRAVITY * randomFloat(1, 10), 0.0));

	this->setLifetime(LIFETIME);
}

void Particle::move(GLfloat floorRadius, GLfloat biggerRadius, GLfloat ground) {
	Position velocity = this->getVelocity();
	Position position = this->getPosition();
	if (position.getY() >= ground) {
		velocity.setY(velocity.getY() + GRAVITY);
		position.setY(position.getY() - velocity.getY());
	} else {
		floorRadius -= this->getSize();
		biggerRadius -= this->getSize();
		position.setX(randomFloat(-floorRadius, floorRadius));
		position.setZ(randomFloat(-floorRadius, floorRadius));
		position.setY(generateAnotherCoordinateOnSurface(floorRadius, 0, position.getX(), position.getZ(), Y));
		position.setY(position.getY() + (biggerRadius - floorRadius));
		velocity.setY(GRAVITY);
	}

	this->setPosition(position);
	this->setVelocity(velocity);
}

void generateParticles(Particle* particles, int numOfParticles, GLfloat floorRadius, GLfloat biggerRadius) {
	for (int i = 0; i < numOfParticles; i++) {
		particles[i].generate(floorRadius, biggerRadius);
	}
}

void moveParticles(GLUquadric* quad, Particle* particles, int numOfParticles, GLfloat floorRadius, GLfloat biggerRadius, GLfloat ground) {
	Sphere snowflake = Sphere(quad, 0.0, 5, 5, Rotation(), Position(), Color(0xFFFFFF));

	for (int i = 0; i < numOfParticles; i++) {
		particles[i].move(floorRadius, biggerRadius, ground);

		snowflake.setSize(particles[i].getSize());
		snowflake.setPosition(particles[i].getPosition());
		snowflake.draw();
	}
}
