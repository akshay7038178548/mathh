#ifndef math_distance_2d_h
#define math_distance_2d_h

#include "fwd.h"

#include "primitives.2d.h"
#include "figures.2d.h"

#include "matrix.ops.h"



namespace math
{
	template <typename T>
	T distance(const point_2d_t<T> &a, const point_2d_t<T> &b)
	{
		return (b - a).length();
	}

	template <typename T>
	T distance(const point_2d_t<T> &p, const line_t<point_2d_t<T>> &l)
	{
		return 0;
		//return l.n() % vector_2d_t<T>(p) + l.p[2];
	}

	template <typename P>
	typename P::t_t distance(const P &p, const line_segment_t<P> &l)
	{
		return distance(p, projection(l.a(), l.b()) * p);
	}
}

#endif // math_distance_2d_h
