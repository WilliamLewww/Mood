#pragma once
#include <iostream>
#include <cmath>
class Vector2 {
public:
	double x, y;

	Vector2();
	Vector2(const Vector2& vector);
	Vector2(double xArgs, double yArgs);
	void expand(double xArgs, double yArgs);
	void shrink(double xArgs, double yArgs);
	int getSignX();
	int getSignY();
	double max();
	double min();
	Vector2 get();
	Vector2 normalize();
	Vector2 vectorAbs();
	Vector2 operator*(Vector2 vector);
	Vector2 operator/(Vector2 vector);
	Vector2 operator*(double value);
	Vector2 operator/(double value);
	Vector2 operator+(Vector2 vector);
	Vector2 operator-(Vector2 vector);
	Vector2 operator+=(Vector2 vector);
	Vector2 operator-=(Vector2 vector);
	Vector2 operator*=(Vector2 vector);
	Vector2 operator/=(Vector2 vector);
	bool operator==(Vector2 vector);
	bool operator!=(Vector2 vector);
	bool operator<(const Vector2& vector) const;
	friend std::ostream &operator<<(std::ostream &os, Vector2 const &m);
};