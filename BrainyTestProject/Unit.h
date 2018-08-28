#pragma once
#include "LinearAlgebra.h"

class Unit
{
private:
	Point m_position;
	Vector2D m_direction;
public:
	Unit() = delete;
	Unit(const Point & position, const Vector2D & direction) : m_position(position), m_direction(direction) {};
	Unit(Point && position, Vector2D && direction) : m_position(position), m_direction(direction) {};
	Point position() const;
	Vector2D direction() const;

	void setPosition(const Point & newPosition);
	void setDirection(const Vector2D & newDirection);
	
	~Unit() = default;
};

