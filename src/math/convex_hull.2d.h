#ifndef math_convex_hull_2d_h
#define math_convex_hull_2d_h

#include "fwd.h"

#include "primitives.2d.h"
#include "figures.2d.h"
#include "distance.2d.h"


namespace math
{
	// O(1)
	template <typename P>
	circle_t<P> circumscribe(const triangle_t<P> &t)
	{
		typename P::v_t ab = t.b() - t.a();
		typename P::v_t ac = t.c() - t.a();
		typename P::t_t d = 2 * (ab.x*ac.y - ab.y*ac.x);
		typename P::v_t c((ac.y*(ab.x*ab.x + ab.y*ab.y) - ab.y*(ac.x*ac.x + ac.y*ac.y))/d
		                , (ab.x*(ac.x*ac.x + ac.y*ac.y) - ac.x*(ab.x*ab.x + ab.y*ab.y))/d);
		return circle_t<P>(P::o + c, c.length());
	}

	// O(1)
	template <typename P>
	triangle_t<P> trianglescribe(const triangle_t<P> &t)
	{
		return t;
	}

//	// O(1)
//	template <typename T>
//	polygon_2d<T> convexscribe(const triangle_2d<T> &p)
//	{
//		return t;
//	}


//	template <typename T, size_t S>
//	circle<T> circumscribe(const polygon_2d<T, S> &p)
//	{
//		throw core::not_implemented();
//	}

//	template <typename T, size_t S>
//	triangle_2d<T> trianglescribe(const polygon_2d<T, S> &p)
//	{
//		throw core::not_implemented();
//	}

	// O(n)
//	template <typename P, size_t S>
//	aabb_2d<T> aabbscribe(const polygon_t<P, S> &p)
//	{
//		point_2d_t<T> min = point_2d_t<T>::max;
//		point_2d_t<T> max = point_2d_t<T>::min;

//		for (size_t i = 0; i < p.size(); i++) {
//			if (p[i].x < min.x) min.x = p[i].x;
//			else if (p[i].x > max.x) max.x = p[i].x;
//			if (p[i].y < min.y) min.y = p[i].y;
//			else if (p[i].y > max.y) max.y = p[i].y;
//		}

//		return aabb_2d<T>(min, max);
//	}

//	template <typename T, size_t S>
//	polygon<T> convexscribe(const polygon<T, S> &p)
//	{
//		throw core::not_implemented();
//	}


//	template <typename T>
//	circle<T> circumscribe(const point_2d_set<T> &ps)
//	{
//		throw core::not_implemented();
//	}

//	template <typename T>
//	triangle_2d<T> trianglescribe(const point_2d_set<T> &ps)
//	{
//		throw core::not_implemented();
//	}

	// O(n)
//	template <typename T>
//	aabb_2d<T> aabbscribe(const point_2d_set<T> &ps)
//	{
//		point_2d_t<T> min = point_2d_t<T>::max;
//		point_2d_t<T> max = point_2d_t<T>::min;

//		for (typename point_2d_set<T>::const_iterator i = ps.begin(); i != ps.end(); ++i) {
//			point_2d_t<T> &p = (*i);
//			if (p.x < min.x) min.x = p.x;
//			else if (p.x > max.x) max.x = p.x;
//			if (p.y < min.y) min.y = p.y;
//			else if (p.y > max.y) max.y = p.y;
//		}

//		return aabb_2d<T>(min, max);
//	}

//	template <typename T>
//	polygon<T> convexscribe(const point_2d_set<T, S> &ps)
//	{
//		throw core::not_implemented();
//	}
}

#endif // math_convex_hull_2d_h
