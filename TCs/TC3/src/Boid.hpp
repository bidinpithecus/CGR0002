#ifndef _BOID_HPP_
#define _BOID_HPP_

#include <vector>
#include "Utils.hpp"
#include "Helpers.hpp"
#include "Shapes.hpp"

class Boid {
	public:
		Boid(Position position);
		Boid(Position lowerLimit, Position upperLimit);
		Boid();
		~Boid();
		void update();
		void show(GLfloat radius, Color color);
		void edges(Position lowerLimit, Position upperLimit);
		Position align(float matchingFactor);
		Position cohesion(float centeringFactor);
		Position separation(float avoidFactor);
		void applyBehaviour(float centeringFactor, float avoidingFactor, float matchingFactor);
		void addNeighbour(Boid boid);

		std::vector<Boid> getNeighbors();
		void setNeighbors(std::vector<Boid> neighbors);
		Position getPosition();
		void setPosition(Position position);
		Position getVelocity();
		void setVelocity(Position velocity);
		Position getAcceleration();
		void setAcceleration(Position acceleration);

	private:
		std::vector<Boid> neighbors;
		Position position;
		Position velocity;
		Position acceleration;
		float maxSpeed;
};

void calculateNeighbors(std::vector<Boid> &swarm, float bound);

#endif
