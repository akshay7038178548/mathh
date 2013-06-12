#ifndef math_contains_h
#define math_contains_h

#include "fwd.h"

#include "contains.2d.h"
#include "contains.3d.h"

#include "position.h"


namespace math
{
	template <typename P, typename I>
	bool contains(const I &b, const I &e, const P &p)
	{
		I pr = b;
		for (I i = b + 1; i < e; ++i) {
			if (!position(p, line_t<P>(*pr, *i)))
				return false;
			pr = i;
		}
		return true;
	}

	template <typename T>
	bool contains(const point_2d_t<T> &a, const aabb_t<point_2d_t<T>> &b)
	{
		return gte(a.x, b.a.x) && gte(a.y, b.a.y)
		    && lte(a.x, b.b.x) && lte(a.y, b.b.y);
	}

	template <typename T>
	bool contains(const aabb_t<point_2d_t<T>> &a, const aabb_t<point_2d_t<T>> &b)
	{
		return contains(a.a, b)
		    || contains(a.b, b)
		    || contains(point_2d_t<T>(a.a.x, a.b.y), b)
		    || contains(point_2d_t<T>(a.b.x, a.a.y), b);
	}

	template <typename P>
	bool contains(const circle_t<P> &c, const P &p)
	{
		return distance(p, c.c) < c.r;
	}
}

#endif // math_contains_h
