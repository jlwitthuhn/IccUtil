#pragma once

#include <array>

#include "Vector.h"

template <typename T>
class Triangle
{
public:
	using Point2d = Vector<T, 2>;

	Triangle(Point2d p1, Point2d p2, Point2d p3) : points{ p1, p2, p3 } {}

	// Based on https://stackoverflow.com/a/20861130
	bool contains(const Point2d point) const
	{
		const double s = (points[0].x() - points[2].x()) * (point.y() - points[2].y()) - (points[0].y() - points[2].y()) * (point.x() - points[2].x());
		const double t = (points[1].x() - points[0].x()) * (point.y() - points[0].y()) - (points[1].y() - points[0].y()) * (point.x() - points[0].x());
		if ((s < 0) != (t < 0) && s != 0 && t != 0)
		{
			return false;
		}

		const double d = (points[2].x() - points[1].x()) * (point.y() - points[1].y()) - (points[2].y() - points[1].y()) * (point.x() - points[1].x());
		return d == 0 || (d < 0) == (s + t <= 0);
	}

	std::array<Point2d, 3> points;
};
