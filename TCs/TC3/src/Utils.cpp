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

float Position::euclidianDistance(Position position) {
	return sqrt(pow(this->getX() - position.getX(), 2) + pow(this->getY() - position.getY(), 2) + pow(this->getZ() - position.getZ(), 2));
}

void Position::plus(Position position) {
	this->x += position.getX();
	this->y += position.getY();
	this->z += position.getZ();
}

void Position::minus(Position position) {
	this->x -= position.getX();
	this->y -= position.getY();
	this->z -= position.getZ();
}

void Position::divide(Position position) {
	this->x /= position.getX();
	this->y /= position.getY();
	this->z /= position.getZ();
}

void Position::mult(Position position) {
	this->x *= position.getX();
	this->y *= position.getY();
	this->z *= position.getZ();
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

