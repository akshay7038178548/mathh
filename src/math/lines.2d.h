#ifndef math_lines_2d_h
#define math_lines_2d_h

#include "fwd.h"

#include "primitives.2d.h"


namespace math
{
	template <typename T>
	struct _base_line_2d
	{
		DECLARE_BASIS_2D(T);


		_base_line_2d()
		{
		}

		_base_line_2d(const _base_line_2d &c)
		{
		}

		template <typename U>
		explicit _base_line_2d(const _base_line_2d<U> &c)
		{
		}
	};


	template <typename T>
	struct line_2d : public _base_line_2d<T>
	{
		INHERIT_BASIS(_base_line_2d<T>);


		static line_2d<T> ox;
		static line_2d<T> oy;


		t_t p[3];
		t_t &a;
		t_t &b;
		t_t &c;


		p_t o() const
		{
			if (p[0] != 0) {
				return p_t(-p[2]/p[0], 0);
			}
			if (p[1] != 0) {
				return p_t(0, -p[2]/p[1]);
			}

			return p_t();
		}

		v_t n() const { return (v_t &)p[0]; }



		line_2d()
			: a(p[0])
			, b(p[1])
			, c(p[2])
		{
			p[0] = p[1] = p[2] = basis<T>::nan();
		}

		line_2d(const p_t &pa, const p_t &pb)
			: a(p[0])
			, b(p[1])
			, c(p[2])
		{
			v_t &pn = (v_t &)p[0];
			pn = (pb - pa).norm().ort();
			p[2] = -(pn % v_t(pa));
		}

		line_2d(const p_t &pa, const v_t &v)
			: a(p[0])
			, b(p[1])
			, c(p[2])
		{
			v_t &pn = (v_t &)p[0];
			pn = v.ort();
			p[2] = -(pn % v_t(pa));
		}

		line_2d(const line_2d &c)
			: a(p[0])
			, b(p[1])
			, c(p[2])
		{
			std::memcpy(p, c.p, 3 * sizeof(T));
		}

		template <typename U>
		explicit line_2d(const line_2d<U> &c)
			: a(p[0])
			, b(p[1])
			, c(p[2])
		{
			p[0] = math_cast<T>(c.p[0]);
			p[1] = math_cast<T>(c.p[1]);
			p[2] = math_cast<T>(c.p[2]);
		}

		line_2d<T> &operator =(const line_2d<T> &r)
		{
			std::memcpy(p, r.p, 3 * sizeof(T));
			return *this;
		}
	};



	template <typename T>
	struct ray_2d : public line_2d<T>
	{
		INHERIT_BASIS(line_2d<T>);


		p_t po;
		v_t d;
	};



	template <typename T>
	struct line_segment_2d : public line_2d<T>
	{
		INHERIT_BASIS(line_2d<T>);


		static line_segment_2d<T> null;


		p_t pa;
		p_t pb;


		line_segment_2d()
			: b_t()
			, pa(p_t::null)
			, pb(p_t::null)
		{
		}
		
		line_segment_2d(const p_t &pa, const p_t &pb)
			: b_t(pa, pb)
			, pa(pa)
			, pb(pb)
		{
		}

		line_segment_2d(const p_t &pa, const v_t v)
			: b_t(pa, v)
			, pa(pa)
			, pb(pa + v)
		{
		}

		line_segment_2d(const line_2d<T> &l, const p_t &pa, const p_t &pb)
			: b_t(l)
			, pa(pa)
			, pb(pb)
		{
		}

		line_segment_2d(const line_segment_2d &c)
			: b_t(c)
			, pa(c.pa)
			, pb(c.pb)
		{
		}

		template <typename U>
		explicit line_segment_2d(const line_segment_2d<U> &c)
			: b_t(c)
			, pa(c.pa)
			, pb(c.pb)
		{
		}		


		p_t operator [](f_t dl) const
		{
			return p_t(pa + (pb - pa) * dl);
		}

		f_t operator [](const p_t &p) const // DEFECT possible fpp error
		{
			if (ne(pa.x, pb.x)) {
				return (p.x - pa.x) / (pb.x - pa.x);
			}
			if (ne(pa.y, pb.y)) {
				return (p.y - pa.y) / (pb.y - pa.y);
			}
			if (ne(pa.z, pb.z)) {
				return (p.z - pa.z) / (pb.z - pa.z);
			}
		}
	};



	template <typename T, size_t S>
	struct poly_line_2d : public _base_line_2d<T>
	{
		INHERIT_BASIS(_base_line_2d<T>);


		p_t p[S];
		f_t u[S];


		p_t o() const { return median<S>(p); }


		poly_line_2d()
		{
		}

		template <typename U>
		poly_line_2d(const poly_line_2d<U, S> &c)
		{
			set(c.p, c.p + c.size());
		}


		template <typename I>
		void set(I begin, I end)
		{
			if (begin == end) return;

			size_t i = 0;
			f_t l = 0;
			u[0] = 0;

			p[i++] = *(begin++);
			while (begin != end) {
				assert(i < size() || !"to many points.");

				p[i] = *(begin++);
				u[i] = (p[i] - p[i - 1]).length();
				l += u[i];
				++i;
			}

			size_t iu;
			for (iu = 1; iu < i; iu++) {
				u[iu] = (p[iu] - p[iu - 1]).length() / u[iu];
			}
			for (; iu < size(); iu++) {
				u[iu] = 0;
			}
		}


		void normalize()
		{
			f_t l = 0;
			u[0] = 0;

			for (size_t i = 1; i < S; i++) {
				u[i] = (p[i] - p[i - 1]).length();
				l += u[i];
			}

			for (size_t i = 1; i < S; i++) {
				u[i] = (p[i] - p[i - 1]).length() / u[i];
			}
		}

		size_t size() const { return S; }
		size_t index(f_t dl) const
		{
			if (u[0] > dl) {
				return 1;
			}

			for (size_t i = 1; i < S; i++) {
				if (u[i] > dl && u[i-1] <= dl) {
					return i;
				}
			}

			return S;
		}
//		line_segment<T> operator [](size_t i) const
//		{
//			return line_segment<T>(p[i], p[(i + 1) % S]);
//		}


		p_t operator [](f_t dl) const
		{
			size_t i = index(dl);
			return line_segment_2d<T>(p[i - 1], p[i])[dl - u[i-1]];
		}

		f_t operator [](const p_t &p) const
		{
			throw 0;//core::not_implemented();
		}


		p_t affine(f_t *w) const
		{
			p_t r;

			for (size_t i = 0; i < S; i++) {
				r.x += p[i].x * w[i];
				r.y += p[i].y * w[i];
			}

			return r;
		}
	};

	template <size_t S, typename T, template <typename> class L>
	poly_line_2d<T, S> approximate(const L<T> &l)
	{
		poly_line_2d<T, S> npl;

		return npl;
	}

	template <size_t S, typename L>
	poly_line_2d<typename L::t_t, S> approximate(const L &l)
	{
		poly_line_2d<typename L::t_t, S> npl;

		return npl;
	}
	


	template <typename T/*, size_t S*/>
	struct bezier_line_2d : public poly_line_2d<T, 4/*S*/>
	{
		typedef poly_line_2d<T, 4/*S*/> _t;
		INHERIT_BASIS(_t);


		p_t operator [](f_t dl) const
		{
			f_t t = dl;
			f_t t2 = t*t;
			f_t u = 1 - dl;
			f_t u2 = u*u;

			f_t w[] = {t*t2, t2*u, t*u2, u*u2};

			return affine(w);
		}

		f_t operator [](const p_t &p) const
		{
			throw 0;//core::not_implemented();
		}
	};



	template <typename T, size_t S>
	struct bspline_line_2d : public poly_line_2d<T, S>
	{
		typedef poly_line_2d<T, S> _t;
		INHERIT_BASIS(_t);


		p_t operator [](f_t dl) const
		{
			throw 0;//core::not_implemented();
		}

		f_t operator [](const p_t &p) const
		{
			throw 0;//core::not_implemented();
		}
	};



	template <typename T>
	struct dynamic_poly_line_2d : public _base_line_2d<T>
	{
		INHERIT_BASIS(_base_line_2d<T>);


		std::vector<p_t> p;
		std::vector<f_t> u;


		p_t o() const { return median<t_t>(p.begin(), p.end()); }


		dynamic_poly_line_2d(size_t s)
			: p(s)
			, u(s)
		{
		}

		template <typename I>
		void set(I begin, I end)
		{
			if (begin == end) return;

			size_t i = 0;
			f_t l = 0;
			u[0] = 0;

			p[i++] = *(begin++);
			while (begin != end) {
				assert(i < size() || !"to many points.");

				p[i] = *(begin++);
				u[i] = (p[i] - p[i - 1]).length();
				l += u[i];
				++i;
			}

			size_t iu;
			for (iu = 1; iu < i; iu++) {
				u[iu] = (p[iu] - p[iu - 1]).length() / u[iu];
			}
			for (; iu < size(); iu++) {
				u[iu] = 0;
			}
		}


		void normalize()
		{
			f_t l = 0;
			u[0] = 0;

			for (size_t i = 1; i < size(); i++) {
				u[i] = (p[i] - p[i - 1]).length();
				l += u[i];
			}

			for (size_t i = 1; i < size(); i++) {
				u[i] = (p[i] - p[i - 1]).length() / u[i];
			}
		}

		size_t size() const { return p.size(); }
		size_t index(f_t dl) const
		{
			if (u[0] > dl) {
				return 1;
			}

			for (size_t i = 1; i < size(); i++) {
				if (u[i] > dl && u[i-1] <= dl) {
					return i;
				}
			}

			return size();
		}


		p_t operator [](f_t dl) const
		{
			size_t i = index(dl);
			return line_segment_2d<T>(p[i - 1], p[i])[dl - u[i-1]];
		}

		f_t operator [](const p_t &p) const
		{
			throw 0;//core::not_implemented();
		}


		p_t affine(f_t *w) const
		{
			p_t r;

			for (size_t i = 0; i < size(); i++) {
				r.x += p[i].x * w[i];
				r.y += p[i].y * w[i];
			}

			return r;
		}
	};

	template <typename T, template <typename> class L>
	dynamic_poly_line_2d<T> approximate(const L<T> &l, int s)
	{
		dynamic_poly_line_2d<T> npl(s);

		return npl;
	}

	template <typename L>
	dynamic_poly_line_2d<typename L::t_t> approximate(const L &l, int s)
	{
		dynamic_poly_line_2d<typename L::t_t> npl(s);

		return npl;
	}
}

#endif // math_lines_2d_h
