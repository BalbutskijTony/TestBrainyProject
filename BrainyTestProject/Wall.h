#pragma once
#include "LinearAlgebra.h"

class Wall
{
private:
	static const int m_countSides = 4;
	Point m_vertices[m_countSides];
	Vector2D m_normals[m_countSides];
	Vector2D m_guides[m_countSides];
	float m_maxX;
	float m_maxY;
	float m_minX;
	float m_minY;
public:
	Wall() = delete;
	Wall(Point p1, Point p2, Point p3, Point p4);
	const Point & vertex(int index) const;
	const Vector2D & normal(int index) const;
	const Vector2D & getGuide(int index) const;
	~Wall() = default;
	const int amountVertices() const;

	float minX() const;
	float minY() const;
	float maxX() const;
	float maxY() const;
};

