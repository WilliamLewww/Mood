#include "vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(const Vector2& vector) {
	x = vector.x;
	y = vector.y;
}

Vector2::Vector2(double xArgs, double yArgs) {
	x = xArgs;
	y = yArgs;
}

int Vector2::getSignX() {
	if (x < 0) {
		return -1;
	}

	return 1;
}

int Vector2::getSignY() {
	if (y < 0) {
		return -1;
	}

	return 1;
}

Vector2 Vector2::get() {
	return Vector2(x, y);
}

Vector2 Vector2::vectorAbs() {
	x = abs(x);
	y = abs(y);

	return *this;
}

void Vector2::expand(double xArgs, double yArgs) {
	x *= xArgs;
	y *= yArgs;
}

void Vector2::shrink(double xArgs, double yArgs) {
	x /= xArgs;
	y /= yArgs;
}

double Vector2::max() {
	if (x > y) {
		return x;
	}

	return y;
}

double Vector2::min() {
	if (x < y) {
		return x;
	}

	return y;
}

Vector2 Vector2::normalize() {
	// | a | = sqrt((ax * ax) + (ay * ay) + (az * az))
	// x = ax / | a |
	// y = ay / | a |
	// z = az / | a |
	double magnitude = (double)abs(sqrt((x * x) + (y * y)));

	if (magnitude != 0) {
		x = x / magnitude;
		y = y / magnitude;
	}

	return *this;
}

Vector2 Vector2::operator*(Vector2 vector) {
	Vector2 newVector(x * vector.x, y * vector.y);
	return newVector;
}

Vector2 Vector2::operator/(Vector2 vector) {
	Vector2 newVector(x / vector.x, y / vector.y);
	return newVector;
}

Vector2 Vector2::operator*(double value) {
	Vector2 newVector(x * value, y * value);
	return newVector;
}

Vector2 Vector2::operator/(double value) {
	Vector2 newVector(x / value, y / value);
	return newVector;
}

Vector2 Vector2::operator+(Vector2 vector) {
	return Vector2(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator-(Vector2 vector) {
	return Vector2(x - vector.x, y - vector.y);
}

Vector2 Vector2::operator+=(Vector2 vector) {
	Vector2 newVector(x += vector.x, y += vector.y);
	return newVector;
}

Vector2 Vector2::operator-=(Vector2 vector) {
	Vector2 newVector(x -= vector.x, y -= vector.y);
	return newVector;
}

Vector2 Vector2::operator*=(Vector2 vector) {
	Vector2 newVector(x *= vector.x, y *= vector.y);
	return newVector;
}

Vector2 Vector2::operator/=(Vector2 vector) {
	Vector2 newVector(x /= vector.x, y /= vector.y);
	return newVector;
}

bool Vector2::operator==(Vector2 vector) {
	if (x == vector.x && y == vector.y) return true;
	return false;
}

bool Vector2::operator!=(Vector2 vector) {
	if (x != vector.x || y != vector.y) return true;
	return false;
}

bool Vector2::operator<(const Vector2& vector) const {
	return x < vector.x || (x == vector.x && y < vector.y);
}

std::ostream &operator<<(std::ostream &os, Vector2 const &m) {
	return os << m.x << "," << m.y;
}