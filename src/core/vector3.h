#pragma once
#include <iostream>
#include <cmath>
#include "vector2.h"
class Vector3 {
public:
	double x, y, z;

	Vector3();
	Vector3(Vector2 vector, double zArgs);
	Vector3(double xArgs, double yArgs, double zArgs);
	double max();
	double min();
	Vector3 get();
	Vector3 normalize();
	Vector3 vectorAbs();
	Vector3 operator*(Vector3 vector);
	Vector3 operator/(Vector3 vector);
	Vector3 operator*(double value);
	Vector3 operator+(Vector3 vector);
	Vector3 operator-(Vector3 vector);
	Vector3 operator+=(Vector3 vector);
	Vector3 operator-=(Vector3 vector);
	Vector3 operator*=(Vector3 vector);
	Vector3 operator/=(Vector3 vector);
	bool operator==(Vector3 vector);
	bool operator!=(Vector3 vector);
	friend std::ostream &operator<<(std::ostream &os, Vector3 const &m);
};