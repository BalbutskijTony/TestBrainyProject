#include "Unit.h"


Point Unit::position() const {
	return m_position;
}

Vector2D Unit::direction() const {
	return m_direction;
}

void Unit::setPosition(const Point & pos) {
	m_position = pos;
}

void Unit::setDirection(const Vector2D & dir) {
	m_direction = dir;
}