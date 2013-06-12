#ifndef math_intersection_2d_h
#define math_intersection_2d_h

#include "fwd.h"

#include "primitives.2d.h"
#include "figures.2d.h"
#include "distance.2d.h"


namespace math
{
	template <typename T>
	point_2d_t<T> intersection(const line_t<point_2d_t<T>> &l, const line_t<point_2d_t<T>> &r)
	{
		return point_2d_t<T>::null;
		/*
		T nx = l.b * r.a - l.a * r.b;

		if (nx == 0) { // lines are parallel. return some nonpoint.
			return point_2d_t<T>::null;
		}

		T x = - (l.b * r.c - l.c * r.b) / nx;
		T y = - (l.c * r.a - l.a * r.c) / nx;

		return point_2d_t<T>(x, y);
		*/
	}

	template <typename T>
	line_segment_t<point_2d_t<T>> intersection(const circle_t<point_2d_t<T> > &c, const line_t<point_2d_t<T>> &l)
	{
		T d = distance(c.o(), l);
		T ad = std::abs(d);

		if (ad > c.r) {
			return line_segment_t<point_2d_t<T>>::null;
		}

		return line_segment_t<point_2d_t<T>>::null;/*point_2d_t<T> ip = intersection(line_t<point_2d_t<T>>(c.o(), l.n()), l);

		if (ad == c.r) {
			return line_segment_t<point_2d_t<T>>(l, ip, ip);
		}

		return line_segment_t<point_2d_t<T>>(l, ip, ip);*/
	}
}

#endif // math_intersection_2d_h
