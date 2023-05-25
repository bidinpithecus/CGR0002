#include "Coordinate3D.hpp"
#include <cmath>

Coordinate3D::Coordinate3D() : x(0), y(0), z(0) {}
Coordinate3D::Coordinate3D(float same) : x(same), y(same), z(same) {}
Coordinate3D::Coordinate3D(float x, float y, float z) : x(x), y(y), z(z) {}
Coordinate3D::~Coordinate3D() {}

float Coordinate3D::getX() { return this->x; }
float Coordinate3D::getY() { return this->y; }
float Coordinate3D::getZ() { return this->z; }

void Coordinate3D::setX(float x) { this->x = x; }
void Coordinate3D::setY(float y) { this->y = y; }
void Coordinate3D::setZ(float z) { this->z = z; }

bool Coordinate3D::operator==(Coordinate3D coordinate) {
	bool sameX = this->x == coordinate.x;
	bool sameY = this->y == coordinate.y;
	bool sameZ = this->z == coordinate.z;
	return sameX && sameY && sameZ;
}

bool Coordinate3D::operator!=(Coordinate3D coordinate) {
	bool diffX = this->x != coordinate.x;
	bool diffY = this->y != coordinate.y;
	bool diffZ = this->z != coordinate.z;
	return diffX || diffY || diffZ;
}

Coordinate3D Coordinate3D::operator+(Coordinate3D coordinate) {
	return Coordinate3D(this->x + coordinate.x, this->y + coordinate.y, this->z + coordinate.z);
}

Coordinate3D Coordinate3D::operator-(Coordinate3D coordinate) {
	return Coordinate3D(this->x - coordinate.x, this->y - coordinate.y, this->z - coordinate.z);
}

Coordinate3D Coordinate3D::operator*(float num) {
	return Coordinate3D(this->x * num, this->y * num, this->z * num);
}

Coordinate3D Coordinate3D::operator/(float num) {
	if (!num) { num = 1; }
	return Coordinate3D(this->x / num, this->y / num, this->z / num);
}

void Coordinate3D::operator+=(Coordinate3D coordinate) {
	*this = *this + coordinate;
}

void Coordinate3D::operator-=(Coordinate3D coordinate) {
	*this = *this - coordinate;
}

void Coordinate3D::operator*=(float num) {
	*this = *this * num;
}

void Coordinate3D::operator/=(float num) {
	*this = *this / num;
}

float Coordinate3D::squaredDistance(Coordinate3D coordinate) {
	return
		pow(this->x - coordinate.x, 2) +
		pow(this->y - coordinate.y, 2) +
		pow(this->z - coordinate.z, 2);
}

float Coordinate3D::magnitude() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}
