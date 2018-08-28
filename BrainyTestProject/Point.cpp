#include "Point.h"



Point::Point(float x, float y) {
	m_x = x;
	m_y = y;
}

void Point::setX(float x) {
	m_x = x;
}

void Point::setY(float y) {
	m_y = y;
}

float Point::x() const {
	return static_cast<float>(m_x);
}

float Point::y() const {
	return static_cast<float>(m_y);
}

Point operator+(const Point & left, const Point & right) {
	return Point(left.x() + right.x(), left.y() + right.y());
}

Point operator+(const Point & left, const Vector2D & right) {
	return Point(left.x() + right.x(), left.y() + right.y());
}

Point operator+(const Vector2D & left, const Point & right) {
	return Point(left.x() + right.x(), left.y() + right.y());
}

Vector2D operator+(const Vector2D & left, const Vector2D & right) {
	return Vector2D(left.x() + right.x(), left.y() + right.y());
}

Point operator*(const Point & left, const float right) {
	return Point(left.x() * right, left.y() * right);
}

Point operator*(const float right, const Point & left) {
	return Point(left.x() * right, left.y() * right);
}

Vector2D operator*(const Vector2D & left, const float right) {
	return Vector2D(left.x() * right, left.y() * right + 0.5f);
}

Vector2D operator*(const float right, const Vector2D & left) {
	return Vector2D(left.x() * right, left.y() * right);
}

void Point::operator=(const Point & right) {
	m_x = right.m_x;
	m_y = right.m_y;
}

void Vector2D::operator=(const Vector2D & right) {
	setX(right.x());
	setY(right.y());
}

Point operator-(const Point & left, const Point & right) {
	return Point(left.x() - right.x(), left.y() - right.y());
}

Vector2D operator-(const Vector2D & vect) {
	return Vector2D(-vect.x(), -vect.y());
}

bool operator==(const Vector2D & left, const Vector2D & right) {
	return (left.x() == right.x()) && (left.y() == right.y());
}