#include "vector2d.h"

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vector) {
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const double& factor) {
	x *= factor;
	y *= factor;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vector) {
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const double& factor) {
	x /= factor;
	y /= factor;

	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vector) {
	Vector2D v = *this;
	return v += vector;
}

Vector2D Vector2D::operator-(const Vector2D& vector) {
	Vector2D v = *this;
	return v -= vector;
}

Vector2D Vector2D::operator*(const Vector2D& vector) {
	Vector2D v = *this;
	return v *= vector;
}

Vector2D Vector2D::operator*(const double& factor) {
	Vector2D v = *this;
	return v *= factor;
}

Vector2D Vector2D::operator/(const Vector2D& vector) {
	Vector2D v = *this;
	return v /= vector;
}

Vector2D Vector2D::operator/(const double& factor) {
	Vector2D v = *this;
	return v *= factor;
}

bool Vector2D::operator==(const Vector2D& vector) {
	return ((x == vector.x) && (y == vector.y));
}

bool Vector2D::operator!=(const Vector2D& vector) {
	return ((x != vector.x) || (y != vector.y));
}

double Vector2D::magnitude() {
	return std::sqrt(x * x + y * y);
}

Vector2D& Vector2D::normalize() {
	double m = magnitude();

	if (m != 0.0) {
		x /= m;
		y /= m;
	}

	return *this;
}
