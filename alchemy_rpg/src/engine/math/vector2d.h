#pragma once

#include <cmath>

namespace Engine
{
	class Vector2D {
	public:
		double x, y;

		Vector2D() :
			x(0.0), y(0.0)
		{};
		Vector2D(double x1, double y1) :
			x(x1), y(y1)
		{};
		Vector2D(const Vector2D& vector) :
			x(vector.x), y(vector.y)
		{};

		Vector2D& operator+=(const Vector2D& vector);
		Vector2D& operator-=(const Vector2D& vector);

		Vector2D& operator*=(const Vector2D& vector);
		Vector2D& operator*=(const double& factor);

		Vector2D& operator/=(const Vector2D& vector);
		Vector2D& operator/=(const double& factor);


		Vector2D operator+(const Vector2D& vector);
		Vector2D operator-(const Vector2D& vector);

		Vector2D operator*(const Vector2D& vector);
		Vector2D operator*(const double& factor);

		Vector2D operator/(const Vector2D& vector);
		Vector2D operator/(const double& factor);


		bool operator==(const Vector2D& vector);
		bool operator!=(const Vector2D& vector);


		double magnitude();
		Vector2D& normalize();
	};
}

