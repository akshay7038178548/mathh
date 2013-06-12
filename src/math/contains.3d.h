#ifndef math_contains_3d_h
#define math_contains_3d_h

#include "fwd.h"

#include "primitives.3d.h"
#include "figures.3d.h"
#include "distance.3d.h"

#include "contains.2d.h"


namespace math
{
	template <typename T>
	bool contains(const point_3d_t<T> &a, const line_t<point_3d_t<T>> &b)
	{
		return is_zero(distance(a, b));
	}

	template <typename T>
	bool contains(const point_3d_t<T> &a, const line_segment_t<point_3d_t<T>> &b)
	{
		if (!contains(a, (line_t<point_3d_t<T>> &)b))
			return false;

		T t = b[a];
		return t >= 0.f && t <= 1.f;
	}

	template <typename T>
	bool contains(const point_3d_t<T> &a, const plane<T> &b)
	{
		return is_zero(vector_3d_t<T>(a) % b.n() + b.d);
	}
/*
	template <typename T, template <typename> class B>
	bool contains(const point_3d_t<T> &a, const face<T, B> &b)
	{
		if (!contains(a, (plane<T> &)b))
			return false; // possibly assert;

		return math2d::contains(b.project(a), b.b);
	}
*/

	template <typename T>
	T contains(const point_3d_t<T> &p, const frustrum<T> &f)
	{
		T d;

		d = distance(p, f.left_face);   if (d<0) return 0;
		d = distance(p, f.right_face);  if (d<0) return 0;
		d = distance(p, f.bottom_face); if (d<0) return 0;
		d = distance(p, f.top_face);    if (d<0) return 0;
		d = distance(p, f.far_face);    if (d<0) return 0;
		d = distance(p, f.near_face);   if (d<0) return 0;

		return d;
	}

	/*
	template <typename T>
	T contains(const sphere<T> &s, const frustrum<T> &f)
	{
		T d;

		d = distance(s.o(), f.left_face);   if (d<-s.r) return 0;
		d = distance(s.o(), f.right_face);  if (d<-s.r) return 0;
		d = distance(s.o(), f.bottom_face); if (d<-s.r) return 0;
		d = distance(s.o(), f.top_face);    if (d<-s.r) return 0;
		d = distance(s.o(), f.far_face);    if (d<-s.r) return 0;
		d = distance(s.o(), f.near_face);   if (d<-s.r) return 0;

		return d;
	}
	*/
}

#endif // math_contains_3d_h
