#ifndef math_lines_h
#define math_lines_h

//#include "lines.2d.h"
//#include "lines.3d.h"

namespace math
{
	template <typename P>
	struct line_t
	{
		typedef typename P::p_t p_t;
		typedef typename P::v_t v_t;


		p_t o;
		v_t d;


		line_t()
			: o(), d()
		{
		}

		line_t(const p_t &o, const v_t &d)
			: o(o), d(d)
		{
		}

		line_t(const p_t &a, const p_t &b)
			: o(a), d(b - a)
		{
		}

		template <typename U>
		explicit
		line_t(const line_t<U> &c)
			: o(c.o)
			, d(c.d)
		{
		}
	};

	template <typename P>
	struct ray_t : public line_t<P>
	{
		typedef typename P::p_t p_t;
		typedef typename P::v_t v_t;


		static ray_t<P> ox;
		static ray_t<P> oy;
		static ray_t<P> oz;


		ray_t()
			: line_t<P>()
		{
		}

		ray_t(const p_t &o, const v_t &d)
			: line_t<P>(o, d)
		{
		}

		template <typename U>
		explicit
		ray_t(const ray_t<U> &c)
			: line_t<P>(c)
		{
		}
	};

	template <typename P>
	struct line_segment_t : public line_t<P>
	{
		typedef P p_t;


		static line_segment_t<P> null;


		p_t a() const { return this->o; }
		p_t b() const { return this->o + this->d; }



		line_segment_t()
			: line_t<P>()
		{
		}

		line_segment_t(const p_t &a, const p_t &b)
			: line_t<P>(a, b - a)
		{
		}

		template <typename U>
		explicit
		line_segment_t(const line_segment_t<U> &c)
			: line_t<P>(c)
		{
		}
	};

	template <typename P, size_t S>
	struct poly_line_t
	{
		typedef P p_t;
		typedef typename P::t_t t_t;


	private:
		p_t p[S];
		t_t u[S];
	};

	template <typename P>
	struct dynamic_poly_line_t
	{
		typedef P p_t;
		typedef typename P::t_t t_t;


	private:
		std::vector<p_t> p;
		std::vector<t_t> t;
	};
}

#endif // math_lines_h
