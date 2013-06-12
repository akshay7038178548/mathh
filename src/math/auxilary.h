#ifndef math_auxilary_h
#define math_auxilary_h

#include "fwd.h"


namespace math
{
	template <typename T>
	vector_2d_t<T> normalize_in_rect(const aabb_t<point_2d_t<T>> &r, const vector_2d_t<T> &d)
	{
		T x = d.x/(r.w()/2);
		T y = d.y/(r.h()/2);

		return vector_2d_t<T>(x, y);
	}

	template <typename T>
	vector_3d_t<T> vector_on_sphere(const vector_2d_t<T> &p)
	{
		T z2 = 1 - p.x * p.x - p.y * p.y;
		T z = z2 > 0 ? std::sqrt(z2) : 0;

		return vector_3d_t<T>(p.x, p.y, z).norm();
	}
}

#endif // math_auxilary_h
