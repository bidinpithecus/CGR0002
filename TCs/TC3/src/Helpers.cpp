#include "Helpers.hpp"

float square(const float num) {
	return num * num;
}

int randomNum(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
    // Generate a random float between 0 and 1
    float scale = rand() / (float)RAND_MAX;

    // Scale the random double to the desired range between min and max
    return min + scale * (max - min);
}

Position normalize(Position position) {
    float magnitude = sqrt(square(position.getX()) + square(position.getY()) + square(position.getZ()));
    if (magnitude == 0) {
        return Position(0, 0, 0);
    }
    return Position(position.getX() / magnitude, position.getY() / magnitude, position.getZ() / magnitude);
}

float euclidianNormal(Position position) {
	return sqrt(square(position.getX()) + square(position.getY()) + square(position.getZ()));
}

float map(float value, float in_min, float in_max, float out_min, float out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
