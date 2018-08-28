#pragma once
#include "LinearAlgebra.h"
#include <vector>
using std::vector;

class Bullet
{
public:
	Bullet() = delete;
	Bullet(Bullet && right) = default;
	Bullet(const Bullet & right) = default;
	Bullet(const Point & p, const Vector2D & v) : m_position(p), m_direction(v) { m_trajectory.push_back(p); };
	Bullet(Point && p, Vector2D && v) : m_position(p), m_direction(v) { m_trajectory.push_back(p); };
	~Bullet() = default;

	Point position() const;
	Vector2D direction() const;
	void setPosition(const Point & p);
	void setDirection(const Vector2D & v);
	void setTrajectory(const vector<Point> &);
	const vector<Point> & trajectory() const;
	void addPointTrajectory(const Point & p);

	Bullet & operator=(const Bullet &);
	
	void reduceBounds() { m_numberOfBounces--; };
	bool isReboundsImpossible() { return m_numberOfBounces < 0; };

private:
	Point m_position;
	Vector2D m_direction;
	vector<Point> m_trajectory;
	int m_numberOfBounces = 10;
};

