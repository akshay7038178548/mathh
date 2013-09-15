#ifndef math_intersection_3d_h
#define math_intersection_3d_h

#include "fwd.h"

#include "primitives.3d.h"
#include "figures.3d.h"
#include "distance.3d.h"

#include "intersection.2d.h"


namespace math
{
	template <typename T>
	// line_t (&)
	point_3d_t<T> intersection(const line_t<point_3d_t<T>> &l, const plane<T> &pl)
	{
		T d = pl.n() % -l.d;

		if (d == 0) { // line is parallel to plane
			return point_3d_t<T>::null;
		}

		T n = pl.d + (pl.n() % vector_3d_t<T>(l.o));

		return l.o + l.d * (n/d);
	}

	template <typename T>
	// line_t
	line_segment_t<point_3d_t<T>> intersection(const line_t<point_3d_t<T>> &l, const line_t<point_3d_t<T>> &r)
	{
		vector_3d_t<T> c = l.d * r.d;

		if (is_zero(c.magnitude())) { // lines are parallel
			return line_segment_t<point_3d_t<T>>(l.o, r.o + r.d * ((l.o - r.o) % r.d));
		}

		plane<T> pl(l.o, l.d, c);
		plane<T> pr(r.o, r.d, c);

		return line_segment_t<point_3d_t<T>>(intersection(l, pr), intersection(r, pl));
	}

	template <typename T>
	line_segment_t<point_3d_t<T>> intersection(const circle_t<point_3d_t<T>> &s, const line_t<point_3d_t<T>> &l)
	{
		return line_segment_t<point_3d_t<T>>::null;
	}

	template <typename T>
	line_segment_t<point_3d_t<T>> intersection(const circle_t<point_3d_t<T>> &s, const ray_t<point_3d_t<T>> &l)
	{
		if (l.o == s.o()) {

		}

		return line_segment_t<point_3d_t<T>>::null;
	}

	template <typename T>
	point_3d_t<T> intersection(const circle_t<point_3d_t<T>> &s, const plane<T> &pl)
	{
		T d = distance(s.o(), pl);
		T ad = abs(d);

		if (ad > s.r) {
			return point_3d_t<T>::null;
		}

		point_3d_t<T> ip = intersection(line_t<point_3d_t<T>>(s.o(), pl.n()), pl);
		return ip;
	}
}

#endif // math_intersection_3d_h
