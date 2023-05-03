#include "Helpers.hpp"

int square(const float num) {
	return num * num;
}

int randomNum(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
    // Generate a random float between 0 and 1
    double randomDouble = (double)rand() / RAND_MAX;

    // Scale the random double to the desired range between min and max
    return min + randomDouble * (max - min);
}

Position normalize(Position position) {
	float magnitude = sqrt(square(position.getX()) + square(position.getY()) + square(position.getZ()));

	return Position(position.getX() / magnitude, position.getY() / magnitude, position.getZ() / magnitude);
}

float euclidianNormal(Position position) {
	return sqrt(square(position.getX()) + square(position.getY()) + square(position.getZ()));
}
