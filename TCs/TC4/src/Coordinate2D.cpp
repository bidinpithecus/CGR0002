#include "Coordinate2D.hpp"
#include <cmath>

Coordinate2D::Coordinate2D() : x(0), y(0) {}
Coordinate2D::Coordinate2D(float same) : x(same), y(same) {}
Coordinate2D::Coordinate2D(float x, float y) : x(x), y(y) {}
Coordinate2D::~Coordinate2D() {}

float Coordinate2D::getX() { return this->x; }
float Coordinate2D::getY() { return this->y; }

void Coordinate2D::setX(float x) { this->x = x; }
void Coordinate2D::setY(float y) { this->y = y; }

bool Coordinate2D::operator==(Coordinate2D coordinate) {
	bool sameX = this->x == coordinate.x;
	bool sameY = this->y == coordinate.y;
	return sameX && sameY;
}

bool Coordinate2D::operator!=(Coordinate2D coordinate) {
	bool diffX = this->x != coordinate.x;
	bool diffY = this->y != coordinate.y;
	return diffX || diffY;
}

Coordinate2D Coordinate2D::operator+(Coordinate2D coordinate) {
	return Coordinate2D(this->x + coordinate.x, this->y + coordinate.y);
}

Coordinate2D Coordinate2D::operator-(Coordinate2D coordinate) {
	return Coordinate2D(this->x - coordinate.x, this->y - coordinate.y);
}

Coordinate2D Coordinate2D::operator*(float num) {
	return Coordinate2D(this->x * num, this->y * num);
}

Coordinate2D Coordinate2D::operator/(float num) {
	if (!num) { num = 1; }
	return Coordinate2D(this->x / num, this->y / num);
}

void Coordinate2D::operator+=(Coordinate2D coordinate) {
	*this = *this + coordinate;
}

void Coordinate2D::operator-=(Coordinate2D coordinate) {
	*this = *this - coordinate;
}

void Coordinate2D::operator*=(float num) {
	*this = *this * num;
}

void Coordinate2D::operator/=(float num) {
	*this = *this / num;
}

float Coordinate2D::squaredDistance(Coordinate2D coordinate) {
	return
		pow(this->x - coordinate.x, 2) +
		pow(this->y - coordinate.y, 2);
}

float Coordinate2D::magnitude() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
