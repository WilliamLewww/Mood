#include "vector3.h"

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(Vector2 vector, double zArgs) {
	 x = vector.x;
	 y = vector.y;
	 z = zArgs;
}

Vector3::Vector3(double xArgs, double yArgs, double zArgs) {
	x = xArgs;
	y = yArgs;
	z = zArgs;
}

Vector3 Vector3::get() {
	return Vector3(x, y, z);
}

Vector3 Vector3::vectorAbs() {
	x = abs(x);
	y = abs(y);
	z = abs(z);

	return *this;
}

double Vector3::max() {
	if (x > y) {
		if (z > x) {
			return z;
		}
		return x;
	}

	return y;
}

double Vector3::min() {
	if (x < y) {
		if (z < x) {
			return z;
		}
		return x;
	}

	return y;
}

Vector3 Vector3::normalize() {
	// | a | = sqrt((ax * ax) + (ay * ay) + (az * az))
	// x = ax / | a |
	// y = ay / | a |
	// z = az / | a |
	double magnitude = (double)abs(sqrt((x * x) + (y * y) + (z * z)));

	if (magnitude != 0) {
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}

	return *this;
}

Vector3 Vector3::operator*(Vector3 vector) {
	Vector3 newVector(x * vector.x, y * vector.y, z * vector.z);
	return newVector;
}

Vector3 Vector3::operator/(Vector3 vector) {
	Vector3 newVector(x / vector.x, y / vector.y, z / vector.z);
	return newVector;
}

Vector3 Vector3::operator*(double value) {
	Vector3 newVector(x * value, y * value, z * value);
	return newVector;
}

Vector3 Vector3::operator+(Vector3 vector) {
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(Vector3 vector) {
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator+=(Vector3 vector) {
	Vector3 newVector(x += vector.x, y += vector.y, z += vector.z);
	return newVector;
}

Vector3 Vector3::operator-=(Vector3 vector) {
	Vector3 newVector(x -= vector.x, y -= vector.y, z -= vector.z);
	return newVector;
}

Vector3 Vector3::operator*=(Vector3 vector) {
	Vector3 newVector(x *= vector.x, y *= vector.y, z *= vector.z);
	return newVector;
}

Vector3 Vector3::operator/=(Vector3 vector) {
	Vector3 newVector(x /= vector.x, y /= vector.y, z /= vector.z);
	return newVector;
}

bool Vector3::operator==(Vector3 vector) {
	if (x == vector.x && y == vector.y && z == vector.z) return true;
	return false;
}

bool Vector3::operator!=(Vector3 vector) {
	if (x != vector.x || y != vector.y || z != vector.z) return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, Vector3 const &m) {
	return os << m.x << "," << m.y << "," << m.z;
}