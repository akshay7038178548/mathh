#ifndef math_clamp_2d_h
#define math_clamp_2d_h

#include "fwd.h"


namespace math
{
	template <typename T>
	point_2d_t<T> &clamp(const aabb_t<point_2d_t<T>> &a, point_2d_t<T> &b)
	{
		b.x = std::min(a.b.x, std::max(a.a.x, b.x));
		b.y = std::min(a.b.y, std::max(a.a.y, b.y));
		return b;
	}

	template <typename T>
	point_2d_t<T> clamp(const aabb_t<point_2d_t<T>> &a, const point_2d_t<T> &b)
	{
		point_2d_t<T> r(b);
		return clamp(a, r);
	}
}

#endif // math_clamp_2d_h
