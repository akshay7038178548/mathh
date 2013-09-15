#ifndef math_primitives_2d_ops_h
#define math_primitives_2d_ops_h

#include "fwd.h"

#include "primitives.2d.h"



namespace math
{
	template <typename T, typename U>
	static bool operator ==(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r);

	template <typename T, typename U>
	static bool operator !=(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r);

	template <typename T, typename U>
	static bool operator <(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r);

	template <typename T, typename U>
	static bool operator >(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r);

	template <typename T>
	static bool is_zero(const _base_primitive_2d<T> &p);

	template <typename T>
	static bool is_null(const _base_primitive_2d<T> &p);

	template <typename P, typename T>
	inline P &operator +=(P &l, const _base_primitive_2d<T> &r);



	template <typename T>
	point_2d_t<T> median(point_2d_t<T> a, point_2d_t<T> b);

	template <size_t S, typename T>
	point_2d_t<T> median(const point_2d_t<T> *p);

	template <typename T, typename I>
	point_2d_t<T> median(I b, I e);


	template <typename T>
	inline point_2d_t<T> operator +(const point_2d_t<T> &r);

	template <typename T>
	inline point_2d_t<T> operator -(const point_2d_t<T> &r);


	template <typename T, typename U>
	static point_2d_t<T> &operator +=(point_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	inline point_2d_t<T> &operator +=(const vector_2d_t<U> &, point_2d_t<T> &) = delete;

	template <typename T, typename U>
	static point_2d_t<T> &operator -=(point_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static point_2d_t<T> operator +(const point_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static point_2d_t<T> operator -(const point_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static point_2d_t<T> operator +(const vector_2d_t<T> &l, const point_2d_t<U> &r);

	template <typename T, typename U>
	static point_2d_t<T> operator -(const vector_2d_t<T> &l, const point_2d_t<U> &r);

	template <typename T, typename U>
	static vector_2d_t<T> operator -(const point_2d_t<T> &l, const point_2d_t<U> &r);


	template <typename T, typename U>
	static bool operator <=(const point_2d_t<U> &l, const point_2d_t<U> &r);

	template <typename T, typename U>
	static bool operator >=(const point_2d_t<U> &l, const point_2d_t<U> &r);



	template <typename T>
	T cos(const vector_2d_t<T> &v);

	template <typename T>
	T sin(const vector_2d_t<T> &v);


	template <typename T>
	static vector_2d_t<T> operator -(const vector_2d_t<T> &r);

	template <typename T, typename U>
	static vector_2d_t<T> &operator *=(vector_2d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_2d_t<T> &operator /=(const vector_2d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_2d_t<T> operator *(const vector_2d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_2d_t<T> operator /(const vector_2d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_2d_t<T> operator +(const vector_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static vector_2d_t<T> operator -(const vector_2d_t<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static T operator %(const vector_2d_t<T> &l, const vector_2d_t<U> &r);


	template <typename T, typename U>
	static bool operator <=(const vector_2d_t<U> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static bool operator >=(const vector_2d_t<U> &l, const vector_2d_t<U> &r);


	template <typename T>
	static const vector_2d_t<T> &operator ~(const point_2d_t<T> &p) { return reinterpret_cast<const vector_2d_t<T> &>(p); }


	// _operator

	template <typename T, typename U>
	static bool operator ==(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r)
	{
		return eq(l.y, r.y) && eq(l.x, r.x);
	}

	template <typename T, typename U>
	static bool operator !=(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r)
	{
		return ne(l.y, r.y) || ne(l.x, r.x);
	}
	
	template <typename T, typename U>
	static bool operator <(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r)
	{
		return (lt(l.y, r.y)
			 || (eq(l.y, r.y) && lt(l.x, r.x)));
	}

	template <typename T, typename U>
	static bool operator >(const _base_primitive_2d<T> &l, const _base_primitive_2d<U> &r)
	{
		return (gt(l.y, r.y)
			 || (eq(l.y, r.y) && gt(l.x, r.x)));
	}

	template <typename T>
	static bool is_zero(const _base_primitive_2d<T> &p)
	{
		return math::is_zero(p.x) && math::is_zero(p.y);
	}

	template <typename T>
	static bool is_null(const _base_primitive_2d<T> &p)
	{
		return 	basis<T>::isnan(p.x) || basis<T>::isnan(p.y);
	}


	template <typename P, typename T>
	inline P &operator +=(P &l, const _base_primitive_2d<T> &r)
	{
		l.x += r.x;
		l.y += r.y;
		return l;
	}



	template <typename T>
	point_2d_t<T> median(point_2d_t<T> a, point_2d_t<T> b)
	{
		vector_2d_t<T> d(b - a);
		T two = 2 * basis<T>::one();

		return point_2d_t<T>(a.x + d.x/two, a.y + d.y/two);
	}

	template <size_t S, typename T>
	point_2d_t<T> median(const point_2d_t<T> *p)
	{
		point_2d_t<T> r(p[0]);

		for (size_t i = 1; i < S; i++) {
			r.x += p[i].x;
			r.y += p[i].y;
		}

		r.x /= S;
		r.y /= S;

		return r;
	}

	template <typename T, typename I>
	point_2d_t<T> median(I b, I e)
	{
		size_t s = 1;
		point_2d_t<T> r(*b);

		while (b != e) {
			r.x += (*b).x;
			r.y += (*b).y;
			s++;
		}

		r.x /= s;
		r.y /= s;

		return r;
	}

	template <typename T, typename U>
	static point_2d_t<T> &operator +=(point_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		l.x += math_cast<T>(r.x);
		l.y += math_cast<T>(r.y);

		return l;
	}

	template <typename T, typename U>
	static point_2d_t<T> &operator -=(point_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		l.x -= math_cast<T>(r.x);
		l.y -= math_cast<T>(r.y);

		return l;
	}

	template <typename T, typename U>
	static point_2d_t<T> operator +(const point_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return point_2d_t<T>(math_cast<T>(l.x + r.x), math_cast<T>(l.y + r.y));
	}

	template <typename T, typename U>
	static point_2d_t<T> operator -(const point_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return point_2d_t<T>(math_cast<T>(l.x - r.x), math_cast<T>(l.y - r.y));
	}

	template <typename T, typename U>
	static point_2d_t<T> operator +(const vector_2d_t<T> &l, const point_2d_t<U> &r)
	{
		return point_2d_t<T>(l.x + r.x, l.y + r.y);
	}

	template <typename T, typename U>
	static point_2d_t<T> operator -(const vector_2d_t<T> &l, const point_2d_t<U> &r)
	{
		return point_2d_t<T>(l.x - r.x, l.y - r.y);
	}

	template <typename T, typename U>
	static vector_2d_t<T> operator -(const point_2d_t<T> &l, const point_2d_t<U> &r)
	{
		return vector_2d_t<T>(l.x - r.x, l.y - r.y);
	}


	template <typename T, typename U>
	static bool operator <=(const point_2d_t<T> &l, const point_2d_t<U> &r)
	{
		return lte(l.y, r.y) && lte(l.x, r.x);
	}

	template <typename T, typename U>
	static bool operator >=(const point_2d_t<T> &l, const point_2d_t<U> &r)
	{
		return gte(l.y, r.y) && gte(l.x, r.x);
	}



	template <typename T>
	T cos(const vector_2d_t<T> &v)
	{
		return v.x/v.length();
	}

	template <typename T>
	T sin(const vector_2d_t<T> &v)
	{
		return v.y/v.length();
	}


	template <typename T>
	inline vector_2d_t<T> operator +(const vector_2d_t<T> &r)
	{
		return r;
	}

	template <typename T>
	inline vector_2d_t<T> operator -(const vector_2d_t<T> &r)
	{
		return vector_2d_t<T>(-r.x, -r.y);
	}

	template <typename T, typename U>
	static vector_2d_t<T> &operator *=(vector_2d_t<T> &l, U r)
	{
		l.x *= math_cast<T>(r);
		l.y *= math_cast<T>(r);

		return l;
	}

	template <typename T, typename U>
	static vector_2d_t<T> &operator /=(const vector_2d_t<T> &l, U r)
	{
		l.x /= math_cast<T>(r);
		l.y /= math_cast<T>(r);

		return l;
	}

	template <typename T, typename U>
	static vector_2d_t<T> operator *(const vector_2d_t<T> &l, U r)
	{
		return vector_2d_t<T>(math_cast<T>(l.x * r), math_cast<T>(l.y * r));
	}

	template <typename T, typename U>
	static vector_2d_t<T> operator /(const vector_2d_t<T> &l, U r)
	{
		return vector_2d_t<T>(math_cast<T>(l.x / r), math_cast<T>(l.y / r));
	}

	template <typename T, typename U>
	static vector_2d_t<T> operator +(const vector_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return vector_2d_t<T>(math_cast<T>(l.x + r.x), math_cast<T>(l.y + r.y));
	}

	template <typename T, typename U>
	static vector_2d_t<T> operator -(const vector_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return vector_2d_t<T>(math_cast<T>(l.x - r.x), math_cast<T>(l.y - r.y));
	}

	template <typename T, typename U>
	static T operator %(const vector_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return math_cast<T>(l.x * r.x + l.y * r.y);
	}


	template <typename T, typename U>
	static bool operator <=(const vector_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return lte(l.y, r.y) && lte(l.x, r.x);
	}

	template <typename T, typename U>
	static bool operator >=(const vector_2d_t<T> &l, const vector_2d_t<U> &r)
	{
		return gte(l.y, r.y) && gte(l.x, r.x);
	}
}

#endif // math_primitives_2d_ops_h
