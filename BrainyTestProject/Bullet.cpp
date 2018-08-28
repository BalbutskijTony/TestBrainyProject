#include "Bullet.h"

Point Bullet::position() const {
	return m_position;
}

Vector2D Bullet::direction() const {
	return m_direction;
}

void Bullet::setPosition(const Point & p) {
	m_position = p;
}

void Bullet::setDirection(const Vector2D & v) {
	m_direction = v;
	normalize(m_direction);
}

const vector<Point> & Bullet::trajectory() const {
	return m_trajectory;
}

void Bullet::addPointTrajectory(const Point & p) {
	m_trajectory.push_back(p);
}

void Bullet::setTrajectory(const vector<Point> & right) {
	this->m_trajectory = right;
}

Bullet & Bullet::operator=(const Bullet & right) {
	this->setDirection(right.direction());
	this->setPosition(right.position());
	this->setTrajectory(right.trajectory());
	return *this;
}

