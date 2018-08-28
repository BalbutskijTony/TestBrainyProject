#pragma once
#include "Point.h"
#include <algorithm>

namespace {
	void rotate(Vector2D & vect, const float angle) {
		float newX = static_cast<float>(cos(M_PI*angle / 180) * vect.x() - sin(M_PI*angle / 180) * vect.y());
		float newY = static_cast<float>(sin(M_PI*angle / 180) * vect.x() + cos(M_PI*angle / 180) * vect.y());

		vect.setX(newX);
		vect.setY(newY);
	}

	Vector2D createRotated(const Vector2D & oldDirection, const float angle) {
		float newX = static_cast<float>(cos(M_PI*angle / 180) * oldDirection.x() - sin(M_PI*angle / 180) * oldDirection.y());
		float newY = static_cast<float>(sin(M_PI*angle / 180) * oldDirection.x() + cos(M_PI*angle / 180) * oldDirection.y());

		return Vector2D(newX, newY);
	}

	void move(Point & p, const Vector2D & vect, const int shift) {
		p.setX(p.x() + shift * vect.x());
		p.setY(p.y() + shift * vect.y());
	}

	Point createShiftedPoint(const Point & p, const Vector2D & vect, const int shift) {
		return Point(p.x() + int(vect.x() * shift + 0.5), p.y() + int(vect.y() * shift + 0.5));
	}

	void normalize(Vector2D & vect) {
		double x = vect.x();
		double y = vect.y();
		float norm = static_cast<float>(sqrt(x * x + y * y));
		vect.setX(static_cast<float>(x / norm));
		vect.setY(static_cast<float>(y / norm));
	}

	float norm(const Vector2D & vect) {
		return sqrt(vect.x() * vect.x() + vect.y() * vect.y());
	}

	bool isSegmentsIntersect(const Point startA, const Point endA, const Point startB, const Point endB, Point & out)
	{
		Point dir1 = endA - startA;
		Point dir2 = endB - startB;

		//считаем уравнения прямых проходящих через отрезки
		float a1 = -dir1.y();
		float b1 = +dir1.x();
		float d1 = -(a1*startA.x() + b1 * startA.y());

		float a2 = -dir2.y();
		float b2 = +dir2.x();
		float d2 = -(a2*startB.x() + b2 * startB.y());

		//подставляем концы отрезков, для выяснения в каких полуплоскотях они
		float segA_line2_start = a2 * startA.x() + b2 * startA.y() + d2;
		float segA_line2_end = a2 * endA.x() + b2 * endA.y() + d2;

		float segB_line1_start = a1 * startB.x() + b1 * startB.y() + d1;
		float segB_line1_end = a1 * endB.x() + b1 * endB.y() + d1;

		//если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
		if (segA_line2_start * segA_line2_end >= 0 || segB_line1_start * segB_line1_end >= 0)
			return false;

		float u = segA_line2_start / (segA_line2_start - segA_line2_end);
		out = startA + u * dir1;

		return true;
	}

	float length(const Point & start, const Point & end) {
		return sqrt((end.x() - start.x())*(end.x() - start.x()) + (end.y() - start.y())*(end.y() - start.y()));
	}

	bool isInside(const Point & point, const Point & start, const Point & end) {
		return (start.x() < point.x() && start.y() < point.y() &&
			end.x() > point.x() && end.y() > point.y());
	}

	Point getIntersection(const Point & startA, const Point & endA, const Point & startB, const Point & endB) {
		double coeff;
		coeff =  (endB.x() - startB.x()) * (startA.y() - startB.y()) - 
				 (endB.y() - startB.y()) * (startA.x() - startB.x());
		coeff /= (endB.y() - startB.y()) * (endA.x() - startA.x()) - 
				 (endB.x() - startB.x()) * (endA.y() - startA.y());

		return startA + (endA - startA) * static_cast<float>(coeff);
	}

	float scalarProduct(const Vector2D & l_op, const Vector2D & r_op) {
		return l_op.x()*r_op.x() + l_op.y()*r_op.y();
	}

	bool isIntersectCircle(const Point & center, float radius, const Point & start, const Point & end)
	{
		float x01 = start.x() - center.x();
		float y01 = start.y() - center.y();
		float x02 = end.x() - center.x();
		float y02 = end.y() - center.y();

		float dx = x02 - x01;
		float dy = y02 - y01;

		float a = dx * dx + dy * dy;
		float b = 2.0f*(x01*dx + y01 * dy);
		float c = x01 * x01 + y01 * y01 - radius * radius;

		if (-b<0)return (c<0);
		if (-b<(2.0f*a))return (4.0f*a*c - b * b<0);
		return (a + b + c<0);
	}
}


