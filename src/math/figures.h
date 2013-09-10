#ifndef math_figures_h
#define math_figures_h

#include "fwd.h"

#include "figures.2d.h"
#include "figures.3d.h"

#include "lines.h"


namespace math
{
	template <typename P>
	struct aabb_t
	{
		typedef P p_t;
		typedef typename P::v_t v_t;
		typedef typename P::t_t t_t;

		p_t a;
		p_t b;
		p_t ab() const { return p_t(a.x, b.y); }
		p_t ba() const { return p_t(b.x, a.y); }
		p_t p(int i) const
		{
			return p_t(!(i & 0x01) ? a.x : b.x
			         , !(i & 0x02) ? a.y : b.y
			         , !(i & 0x03) ? a.z : b.z);
		}


		p_t o() const { return median(a, b); }
		v_t v() const { return b - o(); }
		t_t w() const { return b.x - a.x; }
		t_t h() const { return b.y - a.y; }

		std::pair<std::pair<t_t, t_t>, std::pair<t_t, t_t>> xywh() const { return {{a.x, a.y}, {w(), h()}}; }


		aabb_t()
		{
		}

		/*
		explicit
		aabb_t(t_t r)
			: a(-r, -r)
			, b(r, r)
		{
		}
		*/

		explicit
		aabb_t(const p_t &d)
			: a(p_t::o)
			, b(d)
		{
		}

		explicit
		aabb_t(const v_t &r)
			: a(p_t::o - r)
			, b(p_t::o + r)
		{
		}

		aabb_t(const p_t &a, const p_t &b)
			: a(a)
			, b(b)
		{
		}

		aabb_t(const p_t &o, const v_t &v)
			: a(o - v)
			, b(o + v)
		{
		}

		aabb_t(std::initializer_list<t_t> d)
			: a(d.begin())
			, b(d.begin() + 2)
		{
		}
		
		aabb_t(const aabb_t &c)
			: a(c.a)
			, b(c.b)
		{
		}

		template <typename U>
		explicit aabb_t(const aabb_t<U> &c)
			: a(c.a)
			, b(c.b)
		{
		}

		line_segment_t<P> face(size_t i) const
		{
			switch (i) {
			case 0:
				return line_segment_t<P>(a, ab());
			case 1:
				return line_segment_t<P>(ab(), b);
			case 2:
				return line_segment_t<P>(b, ba());
			case 3:
				return line_segment_t<P>(ba(), a);
			}

			assert(0 && "wrong index of face");
			return line_segment_t<P>::null;
		}


		struct face_iterator {
			face_iterator(const aabb_t *o)
				: o_(o)
				, face_(0)
			{
			}
			face_iterator()
				: face_(4)
			{
			}

			bool operator !=(const face_iterator &o) const { return face_ != o.face_; }
			face_iterator &operator ++() { face_++; return *this; }
			line_segment_t<P> operator *() const { return (*o_).face(face_); }

			const aabb_t *o_;
			int face_;
		};
		face_iterator begin() const { return face_iterator(this); }
		face_iterator end() const { return face_iterator(); }
	};

	template <typename T>
	aabb_t<point_2d_t<T>> make_aabb(T ax, T ay, T bx, T by)
	{
		return aabb_t<point_2d_t<T>>(point_2d_t<T>(ax, ay)
		                           , point_2d_t<T>(bx, by));
	}

	template <typename P>
	bool is_null(const aabb_t<P> &o)
	{
		return is_null(o.a) && is_null(o.b);
	}

	template<typename P>
	static aabb_t<P> &operator +=(aabb_t<P> &l, const typename P::v_t &r);

	template<typename P>
	static aabb_t<P> &operator -=(aabb_t<P> &l, const typename P::v_t &r);

	template <typename P>
	static aabb_t<P> operator +(const aabb_t<P> &l, const typename P::v_t &r);

	template <typename P>
	static aabb_t<P> operator -(const aabb_t<P> &l, const typename P::v_t &r);



	template <typename P, size_t S>
	struct polygon_t
	{
		typedef P p_t;


		p_t p[S];


		p_t o() const { return median<S>(p); }
//		T w() const { throw core::not_implemented(); }
//		T h() const { throw core::not_implemented(); }


		size_t size() const { return S; }
	};



	template <typename P>
	struct triangle_t : public polygon_t<P, 3>
	{
		typedef P p_t;



		p_t a() const { return this->p[0]; }
		p_t b() const { return this->p[1]; }
		p_t c() const { return this->p[2]; }



		triangle_t(const p_t &a, const p_t &b, const p_t &c)
		{
			this->p[0] = a;
			this->p[1] = b;
			this->p[2] = c;
		}

		triangle_t(const p_t *d)
		{
			std::memcpy(p, d, 3 * sizeof(p_t));
		}
		triangle_t(std::initializer_list<p_t> d)
			: triangle_t(d.begin()) {}
	};



	template <typename P>
	struct dynamic_polygon
	{
		typedef P p_t;


		std::vector<p_t> p;


		
	};



	template <typename P>
	struct circle_t
	{
		typedef P p_t;
		typedef typename P::t_t t_t;


		p_t c;
		t_t r;


		p_t o() const { return c; }
		t_t w() const { return r*2; }
		t_t h() const { return r*2; }


		circle_t()
			: c(p_t::o)
			, r(-1)
		{
		}

		explicit
		circle_t(t_t r)
			: c(p_t::o)
			, r(r)
		{
		}

		explicit
		circle_t(const p_t &c)
			: c(c)
			, r(0)
		{
		}

		circle_t(const p_t &c, t_t r)
			: c(c)
			, r(r)
		{
		}

		circle_t(const circle_t &c)
			: c(c.c)
			, r(c.r)
		{
		}

		template <typename U>
		explicit circle_t(const circle_t<U> &c)
			: c(c.c)
			, r(math_cast<t_t>(c.r))
		{
		}


		bool empty() const
		{
			return r < 0;
		}
	};


	// _operator


	template <typename P>
	static aabb_t<P> operator +(const aabb_t<P> &l, const typename P::v_t &r)
	{
		return aabb_t<P>(l.a + r, l.b + r);
	}
}

#endif // math_figures_h
