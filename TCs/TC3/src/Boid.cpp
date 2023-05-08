#include "Boid.hpp"
#include <iostream>

Boid::Boid(Position position) {
	this->position = position;
	this->velocity = Position(randomFloat(-0.25, 0.25), randomFloat(-0.25, 0.25), randomFloat(-0.25, 0.25));
	this->acceleration = Position(randomFloat(-0.1, 0.1), randomFloat(-1, 1), randomFloat(-0.1, 0.1));
	this->maxForce = 0.3;
	this->maxSpeed = 5;
}

Boid::Boid() {
	this->position = Position(randomFloat(-5, 5), randomFloat(2, 3), randomFloat(-5, 5));
	this->velocity = Position(randomFloat(-0.15, 0.15), 0, randomFloat(-0.15, 0.15));
	this->acceleration = Position(randomFloat(-0.01, 0.01), 0, randomFloat(-0.01, 0.01));
	this->maxForce = 0.3;
	this->maxSpeed = 0.5;
}

Boid::~Boid() {}

void Boid::update() {
    // Add small random acceleration
    acceleration.plus(Position(randomFloat(-0.1, 0.1), 0, randomFloat(-0.1, 0.1)));

    velocity.plus(acceleration);
    position.plus(velocity);

    // Limit velocity
    double speed = euclidianNormal(velocity);
    if (speed > maxSpeed) {
        velocity.divide(Position(speed, 0, speed));
        velocity.mult(Position(maxSpeed, 0, maxSpeed));
    }

    acceleration = Position(0, 0, 0);
}

void Boid::show() {
	GLUquadric* pObj;

	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	Rotation rotation = Rotation();
	Sphere sphere = Sphere(pObj, 0.1, 5, 5, rotation, this->position, Color(0x000000));
	sphere.draw();
}

void Boid::edges(float limitX, float limitY, float limitZ) {
	if (this->position.getX() > limitX) {
		this->position.setX(-limitX);
	} else if (this->position.getX() < -limitX) {
		this->position.setX(limitX);
	}

	if (this->position.getY() > limitY) {
		this->position.setY(0);
	} else if (this->position.getY() < 0) {
		this->position.setY(limitY);
	}

	if (this->position.getZ() > limitZ) {
		this->position.setZ(-limitZ);
	} else if (this->position.getZ() < -limitZ) {
		this->position.setZ(limitZ);
	}
}

Position Boid::align() {
    Position steering(0, 0, 0);
    int total = 0;
    Position avgVector(0, 0, 0);

    for (Boid boid : this->neighbors) {
		avgVector.plus(boid.velocity);
		total++;
    }

    if (total) {
        avgVector.divide(Position(total, total, total));
        avgVector = normalize(avgVector);
        avgVector.mult(Position(maxSpeed, maxSpeed, maxSpeed));
        avgVector.minus(velocity);
		steering = avgVector;
    }

    return steering;
}

Position Boid::cohesion() {
    Position steering(0, 0, 0);
    int total = 0;
    Position centerOfMass(0, 0, 0);

    for (const Boid& boid : this->neighbors) {
		centerOfMass.plus(boid.position);
		total++;
    }

    if (this->neighbors.size()) {
        centerOfMass.divide(Position(total, total, total));
        centerOfMass.minus(position);
		Position vecToCom = centerOfMass;
        if (euclidianNormal(vecToCom) > 0) {
            vecToCom = normalize(vecToCom);
            vecToCom.mult(Position(maxSpeed, maxSpeed, maxSpeed));
        }

        vecToCom.minus(velocity);
		steering = vecToCom;

        if (euclidianNormal(steering) > maxForce) {
            steering = normalize(steering);
            steering.mult(Position(maxForce, maxForce, maxForce));
        }
    }

    return steering;
}

Position Boid::separation() {
    Position steering(0, 0, 0);
    int total = 0;
    Position avgVector(0, 0, 0);

    for (auto boid : this->neighbors) {
		Position diff = boid.position;
		diff.minus(position);
		double distance = euclidianNormal(diff);
		// printf("(%lf, %lf, %lf)\n", position.getX(), position.getY(), position.getZ());
		diff.divide(Position(distance, distance, distance));
		avgVector.plus(diff);
		total++;
    }

    if (total) {
        avgVector.divide(Position(total, total, total));
        avgVector = normalize(avgVector);

        if (euclidianNormal(steering)) {
            avgVector.mult(Position(maxSpeed, maxSpeed, maxSpeed));
        }

        avgVector.minus(velocity);
		steering = avgVector;

        if (euclidianNormal(steering) > maxForce) {
            steering = normalize(steering);
            steering.mult(Position(maxForce, maxForce, maxForce));
        }
    }

    return steering;
}

void Boid::applyBehaviour() {
	Position alignment = this->align();
	Position cohesion = this->cohesion();
	Position separation = this->separation();

	this->acceleration.plus(alignment);
	this->acceleration.plus(cohesion);
	this->acceleration.plus(separation);
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

/*
	Not normalized, I think this will be a problem;
	Also does not seem optimized, probably some unnecessary loops
*/
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
