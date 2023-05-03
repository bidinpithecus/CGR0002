#ifndef _BOID_HPP_
#define _BOID_HPP_

#include <vector>
#include "Utils.hpp"
#include "Helpers.hpp"
#include "Shapes.hpp"

class Boid {
	public:
		Boid(Position position);
		Boid();
		~Boid();
		void update();
		void show();
		void edges(float limitX, float limitY, float limitZ);
		Position align();
		Position cohesion();
		Position separation();
		void applyBehaviour();
		void addNeighbour(Boid boid);

		std::vector<Boid> getNeighbors();
		void setNeighbors(std::vector<Boid> neighbors);
		Position getPosition();
		void setNeighbors(Position position);
		Position getVelocity();
		void setVelocity(Position velocity);
		Position getAcceleration();
		void setAcceleration(Position acceleration);

	private:
		std::vector<Boid> neighbors;
		Position position;
		Position velocity;
		Position acceleration;
		float maxForce;
		float maxSpeed;
		float maxPerception;

};

void calculateNeighbors(std::vector<Boid>* swarm, float bound);

#endif
