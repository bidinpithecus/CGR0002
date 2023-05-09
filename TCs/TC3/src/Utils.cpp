#include "Utils.hpp"
#include <math.h>

// Rotation stuff
Rotation::Rotation() {};

Rotation::Rotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	this->angle = angle;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Rotation::rotate() {
	glRotatef(this->angle, this->x, this->y, this->z);
}

void Rotation::setAngle(GLfloat angle) {
	this->angle = angle;
}

// Position stuff
Position::Position() {};

Position::Position(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Position::translate() {
	glTranslatef(this->x, this->y, this->z);
}

void Position::setX(GLfloat x) {
	this->x = x;
}

void Position::setY(GLfloat y) {
	this->y = y;
}

void Position::setZ(GLfloat z) {
	this->z = z;
}

GLfloat Position::getX() {
	return this->x;
}

GLfloat Position::getY() {
	return this->y;
}

GLfloat Position::getZ() {
	return this->z;
}

float Position::euclideanDistance(Position position) {
	return sqrt(pow(this->getX() - position.getX(), 2) + pow(this->getY() - position.getY(), 2) + pow(this->getZ() - position.getZ(), 2));
}

float Position::euclideanDistanceSquared(const Position& v) {
    float dx = this->x - v.x;
    float dy = this->y - v.y;
    float dz = this->z - v.z;
    return dx * dx + dy * dy + dz * dz;
}

Position Position::operator+(Position position) {
	return Position(this->getX() + position.getX(), this->getY() + position.getY(), this->getZ() + position.getZ());
}

Position Position::operator-(Position position) {
	return Position(this->getX() - position.getX(), this->getY() - position.getY(), this->getZ() - position.getZ());
}

Position Position::operator*(Position position) {
	return Position(this->getX() * position.getX(), this->getY() * position.getY(), this->getZ() * position.getZ());
}

Position Position::operator/(Position position) {
	if (!position.getX()) position.setX(1.0);
	if (!position.getY()) position.setY(1.0);
	if (!position.getZ()) position.setZ(1.0);
	return Position(this->getX() / position.getX(), this->getY() / position.getY(), this->getZ() / position.getZ());
}

Position Position::operator+(float num) {
	return Position(this->getX() + num, this->getY() + num, this->getZ() + num);
}

Position Position::operator-(float num) {
	return Position(this->getX() - num, this->getY() - num, this->getZ() - num);
}

Position Position::operator*(float num) {
	return Position(this->getX() * num, this->getY() * num, this->getZ() * num);
}

Position Position::operator/(float num) {
	float toDivide = num;
	if (!num) toDivide = 1;
	return Position(this->getX() / toDivide, this->getY() / toDivide, this->getZ() / toDivide);
}

// Scale stuff
Scale::Scale() {};

Scale::Scale(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Scale::scale() {
	glScalef(this->x, this->y, this->z);
}

void Scale::setX(GLfloat x) {
	this->x = x;
}

void Scale::setY(GLfloat y) {
	this->y = y;
}

void Scale::setZ(GLfloat z) {
	this->z = z;
}

GLfloat Scale::getX() {
	return this->x;
}

GLfloat Scale::getY() {
	return this->y;
}

GLfloat Scale::getZ() {
	return this->z;
}

