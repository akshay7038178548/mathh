#ifndef math_primitives_3d_ops_h
#define math_primitives_3d_ops_h

#include "fwd.h"

#include "primitives.3d.h"



namespace math
{
	template <typename T>
	bool is_zero(const _base_primitive_3d<T> &p);

	template <typename T>
	bool is_null(const _base_primitive_3d<T> &p);


	template <typename T, typename U>
	static bool operator ==(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r);

	template <typename T, typename U>
	static bool operator !=(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r);

	
	template <typename T, typename U>
	static bool operator <(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r);

	template <typename T, typename U>
	static bool operator >(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r);



	template <typename T>
	point_3d_t<T> median(const point_3d_t<T> &a, const point_3d_t<T> &b);

	template <size_t S, typename T>
	point_3d_t<T> median(const point_3d_t<T> *p);

	template <typename T, typename I>
	point_3d_t<T> median(I b, I e);


	template <typename T>
	static const vector_3d_t<T> &operator ~(const point_3d_t<T> &r) { return *reinterpret_cast<const vector_3d_t<T> *>(&r); }

	template <typename T>
	static point_3d_t<T> operator -(const point_3d_t<T> &r);


	template <typename T, typename U>
	static point_3d_t<T> &operator +=(point_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static point_3d_t<T> &operator -=(point_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static point_3d_t<T> operator +(const point_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static point_3d_t<T> operator -(const point_3d_t<T> &l, const vector_3d_t<U> &r);

//	template <typename T, typename U>
//	static point_3d_t<T> operator +(const vector_3d_t<T> &l, const point_3d_t<U> &r);

//	template <typename T, typename U>
//	static point_3d_t<T> operator -(const vector_3d_t<T> &l, const point_3d_t<U> &r);

	template <typename T, typename U>
	static vector_3d_t<T> operator -(const point_3d_t<T> &l, const point_3d_t<U> &r);

	

	template <typename T, typename U>
	static bool operator <=(const point_3d_t<U> &l, const point_3d_t<U> &r);

	template <typename T, typename U>
	static bool operator >=(const point_3d_t<U> &l, const point_3d_t<U> &r);



	template <typename T>
	static vector_3d_t<T> operator -(const vector_3d_t<T> &r);


	template <typename T, typename U>
	static vector_3d_t<T> &operator *=(vector_3d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_3d_t<T> &operator /=(vector_3d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_3d_t<T> operator *(U l, const vector_3d_t<T> &r);

	template <typename T, typename U>
	static vector_3d_t<T> operator *(const vector_3d_t<T> &l, U r);

	template <typename T, typename U>
	static vector_3d_t<T> operator /(const vector_3d_t<T> &l, U r);


	template <typename T, typename U>
	static vector_3d_t<T> &operator +=(vector_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static vector_3d_t<T> &operator -=(vector_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static vector_3d_t<T> operator +(const vector_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static vector_3d_t<T> operator -(const vector_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static T operator %(const vector_3d_t<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static vector_3d_t<T> operator *(const vector_3d_t<T> &l, const vector_3d_t<U> &r);


	template <typename T, typename U>
	static bool operator <=(const vector_3d_t<U> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static bool operator >=(const vector_3d_t<U> &l, const vector_3d_t<U> &r);


	// _operator

	template <typename T>
	bool is_zero(const _base_primitive_3d<T> &p)
	{
		return is_zero((const _base_primitive_2d<T> &)p) && math::is_zero(p.z);
	}

	template <typename T>
	bool is_null(const _base_primitive_3d<T> &p)
	{
		return is_null((const _base_primitive_2d<T> &)p) || basis<T>::isnan(p.z);
	}

	template <typename T, typename U>
	static bool operator ==(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r)
	{
		return eq(l.z, r.z) && eq(l.y, r.y) && eq(l.x, r.x);
	}

	template <typename T, typename U>
	static bool operator !=(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r)
	{
		return neq(l.z, r.z) || neq(l.y, r.y) || neq(l.x, r.x);
	}
	
	template <typename T, typename U>
	static bool operator <(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r)
	{
		return lt(l.z, r.z)
		    || (eq(l.z, r.z) && (lt(l.y, r.y)
		                     || (eq(l.y, r.y) && lt(l.x, r.x))));
	}

	template <typename T, typename U>
	static bool operator >(const _base_primitive_3d<T> &l, const _base_primitive_3d<U> &r)
	{
		return gt(l.z, r.z)
		    || (eq(l.z, r.z) && (gt(l.y, r.y)
		                     || (eq(l.y, r.y) && gt(l.x, r.x))));
	}



	template <typename T>
	point_3d_t<T> median(const point_3d_t<T> &a, const point_3d_t<T> &b)
	{
		T two = 2 * basis<T>::one();
		return point_3d_t<T>(a.x + (b.x - a.x)/two, a.y + (b.y - a.y)/two, a.z + (b.z - a.z)/two);
	}

	template <size_t S, typename T>
	point_3d_t<T> median(const point_3d_t<T> *p)
	{
		point_3d_t<T> r(p[0]);

		for (size_t i = 1; i < S; i++) {
			r.x += p[i].x;
			r.y += p[i].y;
			r.z += p[i].z;
		}

		r.x /= S;
		r.y /= S;
		r.z /= S;

		return r;
	}

	template <typename T, typename I>
	point_3d_t<T> median(I b, I e)
	{
		size_t s = 1;
		point_3d_t<T> r(*b);

		while (b != e) {
			r.x += (*b).x;
			r.y += (*b).y;
			r.z += (*b).z;
			s++;
		}

		r.x /= s;
		r.y /= s;
		r.z /= s;

		return r;
	}

	template <typename T>
	static point_3d_t<T> operator -(const point_3d_t<T> &r)
	{
		return point_3d_t<T>(-r.x, -r.y, -r.z);
	}

	template <typename T, typename U>
	point_3d_t<T> &operator +=(point_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		l.x += math_cast<T>(r.x);
		l.y += math_cast<T>(r.y);
		l.z += math_cast<T>(r.z);

		return l;
	}

	template <typename T, typename U>
	point_3d_t<T> &operator -=(point_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		l.x -= math_cast<T>(r.x);
		l.y -= math_cast<T>(r.y);
		l.z -= math_cast<T>(r.z);

		return l;
	}

	template <typename T, typename U>
	static point_3d_t<T> operator +(const point_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return point_3d_t<T>(l.x + math_cast<T>(r.x), l.y + math_cast<T>(r.y), l.z + math_cast<T>(r.z));
	}

	template <typename T, typename U>
	static point_3d_t<T> operator -(const point_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return point_3d_t<T>(l.x - math_cast<T>(r.x), l.y - math_cast<T>(r.y), l.z - math_cast<T>(r.z));
	}

	template <typename T, typename U>
	static point_3d_t<T> operator +(const vector_3d_t<T> &l, const point_3d_t<U> &r)
	{
		return point_3d_t<T>(l.x + math_cast<T>(r.x), l.y + math_cast<T>(r.y), l.z + math_cast<T>(r.z));
	}

	template <typename T, typename U>
	static point_3d_t<T> operator -(const vector_3d_t<T> &l, const point_3d_t<U> &r)
	{
		return point_3d_t<T>(l.x - r.x, l.y - r.y, l.z - r.z);
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator -(const point_3d_t<T> &l, const point_3d_t<U> &r)
	{
		return vector_3d_t<T>(l.x - math_cast<T>(r.x), l.y - math_cast<T>(r.y), l.z - math_cast<T>(r.z));
	}


	template <typename T>
	static vector_3d_t<T> operator -(const vector_3d_t<T> &r)
	{
		return vector_3d_t<T>(-r.x, -r.y, -r.z);
	}

	template <typename T, typename U>
	static vector_3d_t<T> &operator *=(vector_3d_t<T> &l, U r)
	{
		l.x *= math_cast<T>(r);
		l.y *= math_cast<T>(r);
		l.z *= math_cast<T>(r);

		return l;
	}

	template <typename T, typename U>
	static vector_3d_t<T> &operator /=(vector_3d_t<T> &l, U r)
	{
		l.x /= math_cast<T>(r);
		l.y /= math_cast<T>(r);
		l.z /= math_cast<T>(r);

		return l;
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator *(U l, const vector_3d_t<T> &r)
	{
		return vector_3d_t<T>(r.x * math_cast<T>(l), r.y * math_cast<T>(l), r.z * math_cast<T>(l));
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator *(const vector_3d_t<T> &l, U r)
	{
		return vector_3d_t<T>(l.x * math_cast<T>(r), l.y * math_cast<T>(r), l.z * math_cast<T>(r));
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator /(const vector_3d_t<T> &l, U r)
	{
		return vector_3d_t<T>(l.x / math_cast<T>(r), l.y / math_cast<T>(r), l.z / math_cast<T>(r));
	}

	template <typename T, typename U>
	static vector_3d_t<T> &operator +=(vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		l.x += math_cast<T>(r.x);
		l.y += math_cast<T>(r.y);
		l.z += math_cast<T>(r.z);

		return l;
	}

	template <typename T, typename U>
	static vector_3d_t<T> &operator -=(vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		l.x -= math_cast<T>(r.x);
		l.y -= math_cast<T>(r.y);
		l.z -= math_cast<T>(r.z);

		return l;
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator +(const vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return vector_3d_t<T>(l.x + r.x, l.y + r.y, l.z + r.z);
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator -(const vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return vector_3d_t<T>(l.x - r.x, l.y - r.y, l.z - r.z);
	}

	template <typename T, typename U>
	static T operator %(const vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return math_cast<T>(l.x * r.x + l.y * r.y + l.z * r.z);
	}

	template <typename T, typename U>
	static vector_3d_t<T> operator *(const vector_3d_t<T> &l, const vector_3d_t<U> &r)
	{
		return vector_3d_t<T>(math_cast<T>(l.y * r.z - l.z * r.y)
		                  , math_cast<T>(l.z * r.x - l.x * r.z)
		                  , math_cast<T>(l.x * r.y - l.y * r.x));
	}

/*
	template <typename T, typename U>
	static bool operator <=(const vector_3d_t<U> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static bool operator >=(const vector_3d_t<U> &l, const vector_3d_t<U> &r);
*/
}

#endif // math_primitives_3d_h
