#include "Boid.hpp"
#include <iostream>

Boid::Boid(Position position) {
	Position newPos;
	Position newVel;
	Position newAcc;
	newPos = position;

	newVel.setX(randomFloat(-position.getX(), position.getX()));
	newVel.setY(randomFloat(-position.getY(), position.getY()));
	newVel.setZ(randomFloat(-position.getZ(), position.getZ()));

	newAcc.setX(randomFloat(-position.getX(), position.getX()));
	newAcc.setY(randomFloat(-position.getY(), position.getY()));
	newAcc.setZ(randomFloat(-position.getZ(), position.getZ()));

	this->position = newPos;
	this->velocity = newVel / 10;
	this->acceleration = newAcc / 15;
	this->maxSpeed = randomFloat(position.getX() / 40, position.getX() / 10);
}

Boid::Boid(Position lowerLimit, Position upperLimit) {
	Position newVel;
	Position newAcc;
	this->position.setX(randomFloat(lowerLimit.getX(), upperLimit.getX()));
	this->position.setY(randomFloat(lowerLimit.getY(), upperLimit.getY()));
	this->position.setZ(randomFloat(lowerLimit.getZ(), upperLimit.getZ()));

	newVel.setX(randomFloat(upperLimit.getX() / 100, upperLimit.getX() / 10));
	newVel.setY(randomFloat(upperLimit.getY() / 1000, upperLimit.getY() / 500));
	newVel.setZ(randomFloat(upperLimit.getZ() / 100, upperLimit.getZ() / 10));

	newAcc.setX(randomFloat(upperLimit.getX() / 800, upperLimit.getX() / 80));
	newAcc.setY(randomFloat(upperLimit.getY() / 5000, upperLimit.getY() / 1000));
	newAcc.setZ(randomFloat(upperLimit.getZ() / 800, upperLimit.getZ() / 80));

	this->velocity = newVel / 10;
	this->acceleration = newAcc / randomFloat(14.5, 15.5);
	this->maxSpeed = randomFloat(upperLimit.getX() / 99.5, upperLimit.getX() / 100.5);
}

Boid::Boid() {};

Boid::~Boid() {}

void Boid::update() {
	position = position + velocity;
	velocity = velocity + acceleration;

    double speed = euclidianNormal(velocity);
    if (speed > maxSpeed) {
        velocity = (velocity / speed) * maxSpeed;
    }
}

void Boid::show(GLfloat radius, Color color) {
	GLUquadric* pObj;

	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	Rotation rotation = Rotation();
	Sphere sphere = Sphere(pObj, radius, 5, 5, rotation, this->position, color);
	sphere.draw();
}

void Boid::edges(Position lowerLimit, Position upperLimit) {
	if (this->position.getX() >= upperLimit.getX() || this->position.getX() <= lowerLimit.getX()) {
		this->velocity.setX(-this->velocity.getX());
		this->acceleration.setX(-this->acceleration.getX());
	}
	if (this->position.getY() >= upperLimit.getY() || this->position.getY() <= lowerLimit.getY()) {
		this->velocity.setY(-this->velocity.getY());
		this->acceleration.setY(-this->acceleration.getY());
	}
	if (this->position.getZ() >= upperLimit.getZ() || this->position.getZ() <= lowerLimit.getZ()) {
		this->velocity.setZ(-this->velocity.getZ());
		this->acceleration.setZ(-this->acceleration.getZ());
	}
}

Position Boid::align(float matchingFactor) {
	int total = 0;
	Position avgVector(0, 0, 0);

	for (auto boid : this->neighbors) {
		avgVector = avgVector + boid.getVelocity();
		total++;
	}

	if (total) {
		avgVector = avgVector / total;
		avgVector = (avgVector - this->velocity) * matchingFactor;
	}
	return avgVector;
}

Position Boid::cohesion(float centeringFactor) {
    int total = 0;
    Position centerOfMass(0, 0, 0);

    for (Boid& boid : this->neighbors) {
		centerOfMass = centerOfMass + boid.position;
		total++;
    }

    if (total) {
        centerOfMass = centerOfMass / total;
		centerOfMass = centerOfMass - this->position;
		centerOfMass = centerOfMass * centeringFactor;
    }

    return centerOfMass;
}

Position Boid::separation(float avoidFactor) {
	Position move(0, 0, 0);

	for (auto boid : this->neighbors) {
		move = move + (this->getPosition() - boid.getPosition());
	}

	return move * avoidFactor;
}

void Boid::applyBehaviour(float centeringFactor, float avoidingFactor, float matchingFactor) {
	Position resultants = cohesion(centeringFactor) + separation(avoidingFactor) + align(matchingFactor);
	this->acceleration = this->acceleration + resultants;
}

std::vector<Boid> Boid::getNeighbors() {
	return this->neighbors;
}

void Boid::setNeighbors(std::vector<Boid> neighbors) {
	this->neighbors = neighbors;
}

Position Boid::getPosition() {
	return this->position;
}

void Boid::setPosition(Position position) {
	this->position = position;
}

Position Boid::getVelocity() {
	return this->velocity;
}

void Boid::setVelocity(Position velocity) {
	this->velocity = velocity;
}

Position Boid::getAcceleration() {
	return this->acceleration;
}

void Boid::setAcceleration(Position acceleration) {
	this->acceleration = acceleration;
}

void Boid::addNeighbour(Boid boid) {
	this->neighbors.push_back(boid);
}

void calculateNeighbors(std::vector<Boid> &swarm, float bound) {
	std::vector<Boid> empty;
	std::vector<std::pair<Boid, std::vector<float>>> distances;
	for (long unsigned int i = 0; i < swarm.size(); i++) {
		swarm.at(i).setNeighbors(empty);
		std::vector<float> distance;
		for (long unsigned int j = 0; j < swarm.size(); j++) {
			distance.push_back(swarm.at(i).getPosition().euclideanDistance(swarm.at(j).getPosition()));
		}
		distances.push_back(std::make_pair(swarm.at(i), distance));
	}

	int pairNum = 0;
	for (auto pair : distances) {
		auto distance = distances.at(pairNum).second;

		int distNum = 0;
		for (auto dist : distance) {
			if (dist <= bound) {
				swarm.at(pairNum).addNeighbour(distances.at(distNum).first);
			}
		}
		pairNum++;
	}
}
