#ifndef math_figures_2d_h
#define math_figures_2d_h

#include "fwd.h"

#include "primitives.2d.h"
#include "lines.h"

#if 0

namespace math
{
	template <typename T>
	struct _base_figure_2d
	{
		DECLARE_BASIS_2D(T);


		virtual p_t o() const = 0;
		virtual t_t w() const = 0;
		virtual t_t h() const = 0;


		_base_figure_2d()
		{
		}

		_base_figure_2d(const _base_figure_2d &c)
		{
		}

		template <typename U>
		explicit _base_figure_2d(const _base_figure_2d<U> &c)
		{
		}
	};


	template <typename T>
	struct aabb_2d : public _base_figure_2d<T>
	{
		INHERIT_BASIS(_base_figure_2d<T>);

		p_t a;
		p_t b;
		p_t ab() const { return p_t(a.x, b.y); }
		p_t ba() const { return p_t(b.x, a.y); }


		p_t o() const { return median(a, b); }
		v_t v() const { return b - o(); }
		t_t w() const { return b.x - a.x; }
		t_t h() const { return b.y - a.y; }


		aabb_2d()
		{
		}

		explicit
		aabb_2d(t_t r)
			: a(-r, -r)
			, b(r, r)
		{
		}

		explicit
		aabb_2d(const p_t &d)
			: a(p_t::o)
			, b(d)
		{
		}

		explicit
		aabb_2d(const v_t &r)
			: a(p_t::o - r)
			, b(p_t::o + r)
		{
		}

		aabb_2d(const p_t &a, const p_t &b)
			: a(a)
			, b(b)
		{
		}

		aabb_2d(const p_t &o, const v_t &v)
			: a(o - v)
			, b(o + v)
		{
		}

		aabb_2d(const aabb_2d &c)
			: a(c.a)
			, b(c.b)
		{
		}

		template <typename U>
		explicit aabb_2d(const aabb_2d<U> &c)
			: a(c.a)
			, b(c.b)
		{
		}
	};


	template <typename T>
	aabb_2d<T> make_aabb_2d(T ax, T ay, T bx, T by)
	{
		return aabb_2d<T>(point_2d_t<T>(ax, ay), point_2d_t<T>(bx, by));
	}


	template<typename T, typename U>
	static aabb_2d<T> &operator +=(aabb_2d<T> &l, const vector_2d_t<U> &r);

	template<typename T, typename U>
	static aabb_2d<T> &operator -=(aabb_2d<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static aabb_2d<T> operator +(const aabb_2d<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static aabb_2d<T> operator +(const vector_2d_t<T> &l, const aabb_2d<U> &r);

	template <typename T, typename U>
	static aabb_2d<T> operator -(const aabb_2d<T> &l, const vector_2d_t<U> &r);

	template <typename T, typename U>
	static aabb_2d<T> operator -(const vector_2d_t<T> &l, const aabb_2d<U> &r);



	// _operator

	template <typename T, typename U>
	static aabb_2d<T> &operator +=(aabb_2d<T> &l, const vector_2d_t<U> &r)
	{
		l.a += r;
		l.b += r;

		return l;
	}

	template <typename T, typename U>
	static aabb_2d<T> &operator -=(aabb_2d<T> &l, const vector_2d_t<U> &r)
	{
		l.a -= r;
		l.b -= r;

		return l;
	}

	template <typename T, typename U>
	static aabb_2d<T> operator +(const aabb_2d<T> &l, const vector_2d_t<U> &r)
	{
		return aabb_2d<T>(l.a + r, l.b + r);
	}

	template <typename T, typename U>
	static aabb_2d<T> operator +(const vector_2d_t<T> &l, const aabb_2d<U> &r)
	{
		return aabb_2d<T>(l + r.a, l + r.b);
	}

	template <typename T, typename U>
	static aabb_2d<T> operator -(const aabb_2d<T> &l, const vector_2d_t<U> &r)
	{
		return aabb_2d<T>(l.a - r, l.b - r);
	}

	template <typename T, typename U>
	static aabb_2d<T> operator -(const vector_2d_t<T> &l, const aabb_2d<U> &r)
	{
		return aabb_2d<T>(l - r.a, l - r.b);
	}
}

#endif

/*
namespace math
{
	template <typename T>
	aabb_2d<T> add(const aabb_2d<T> &l, const vector_2d_t<T> &r)
	{
		aabb_2d<T> res(l); res += r;
		return res;
	}

	template <typename T>
	aabb_2d<T> sub(const aabb_2d<T> &l, const vector_2d_t<T> &r)
	{
		aabb_2d<T> res(l); res -= r;
		return res;
	}
}
*/

#endif // math_figures_2d_h
