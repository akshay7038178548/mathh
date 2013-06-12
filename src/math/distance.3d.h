#ifndef math_distance_3d_h
#define math_distance_3d_h

#include "fwd.h"

#include "primitives.3d.h"
#include "figures.3d.h"

#include "distance.2d.h"


namespace math
{
	template <typename T>
	T distance(const point_3d_t<T> &a, const point_3d_t<T> &b)
	{
		return (b - a).length();
	}

	template <typename T>
	T distance(const point_3d_t<T> &p, const line_t<point_3d_t<T>> &l)
	{
		return ((p - l.pa) * (p - l.pa - l.v)).length();
	}

	template <typename T>
	T distance(const point_3d_t<T> &p, const plane<T> &pl)
	{
		return pl.n() % vector_3d_t<T>(p) + pl.p[3];
	}

	template <typename T>
	T distance(const line_t<point_3d_t<T>> &l, const line_t<point_3d_t<T>> &r)
	{
		vector_3d_t<T> c = r.n() * l.n();
		T cl = c.length();

		if (!cl) {
			return -1.f;
		}

		return (r.pa - r.pb) % c / cl;
	}
}

#endif // math_distance_3d_h
