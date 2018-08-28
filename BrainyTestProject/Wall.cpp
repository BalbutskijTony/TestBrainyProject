#include "Wall.h"

Wall::Wall(Point p1, Point p2, Point p3, Point p4) : m_vertices{ p1, p2, p3, p4 }, 
	m_normals
	{ 
		Vector2D(p2.y() - p1.y(), p1.x() - p2.x()), 
		Vector2D(p3.y() - p2.y() , p2.x() - p3.x()),
		Vector2D(p4.y() - p3.y(), p3.x() - p4.x()), 
		Vector2D(p1.y() - p4.y(), p4.x() - p1.x()) 
	},
	m_guides{ Vector2D(p2 - p1), Vector2D(p3 - p2), Vector2D(p4 - p3), Vector2D(p1 - p4) } 
{
	
	m_minX = std::min(std::min(p1.x(), p2.x()), std::min(p3.x(), p4.x()));
	m_minY = std::min(std::min(p1.y(), p2.y()), std::min(p3.y(), p4.y()));

	m_maxX = std::max(std::max(p1.x(), p2.x()), std::max(p3.x(), p4.x()));
	m_maxY = std::max(std::max(p1.y(), p2.y()), std::max(p3.y(), p4.y()));

	for (auto &a : m_normals)
		normalize(a);

	for (auto &v : m_guides)
		normalize(v);
}

const Point & Wall::vertex(int index) const {
	if (index < m_countSides)
		return m_vertices[index];
	else
		return m_vertices[index - m_countSides];
}

const Vector2D & Wall::getGuide(int index) const {
	return m_guides[index];
}

const int Wall::amountVertices() const {
	return m_countSides;
}

const Vector2D & Wall::normal(int index) const {
	return m_normals[index];
}

float Wall::minX() const {
	return m_minX;
}

float Wall::minY() const {
	return m_minY;
}

float Wall::maxX() const {
	return m_maxX;
}

float Wall::maxY() const {
	return m_maxY;
}