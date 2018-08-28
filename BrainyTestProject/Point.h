#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <utility>

class Point
{
private:
	double m_x;
	double m_y;
public:
	Point() : m_x(0), m_y(0) {};
	Point(float x, float y);
	Point(const Point & p) = default;
	Point(Point && p) = default;

	void setX(float x);
	void setY(float y);
	float x() const;
	float y() const;
	virtual ~Point() = default;

	void operator=(const Point & right);
};

struct Vector2D final : public Point {
	Vector2D() : Point() {};
	Vector2D(Point && p) : Point(std::move(p)) {};
	Vector2D(float x, float y) : Point(x, y) {};
	Vector2D(const Vector2D & p) = default;
	Vector2D(Vector2D && p) = default;
	virtual ~Vector2D() = default;

	void operator=(const Vector2D & right);
};

Point operator+(const Point & left, const Point & right);
Point operator+(const Point & left, const Vector2D & right);
Point operator+(const Vector2D & left, const Point & right);
Point operator-(const Point & left, const Point & right);
Point operator*(const Point & left, const float right);
Point operator*(const float right, const Point & left);

Point operator+(const Point & left, const Vector2D & right);
Point operator+(const Vector2D & left, const Point & right);
Vector2D operator+(const Vector2D & left, const Vector2D & right);
Vector2D operator*(const Vector2D & left, const float right);
Vector2D operator*(const float right, const Vector2D & left);

Vector2D operator-(const Vector2D & vect);
bool operator==(const Vector2D & left, const Vector2D & right);