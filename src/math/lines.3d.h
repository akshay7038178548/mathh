#ifndef math_lines_3d_h
#define math_lines_3d_h

#include "primitives.3d.h"

//#include "lines.2d.h"


namespace math
{
	template <typename T>
	struct _base_line_3d
	{
		DECLARE_BASIS_3D(T);


//		virtual p_t o() const = 0;
//		virtual v_t n() const = 0;


		_base_line_3d()
		{
		}

		_base_line_3d(const _base_line_3d &c)
		{
		}

		template <typename U>
		explicit _base_line_3d(const _base_line_3d<U> &c)
		{
		}
	};



	template <typename T>
	struct line_3d : public _base_line_3d<T>
	{
		INHERIT_BASIS(_base_line_3d<T>);


		static line_3d<T> ox;
		static line_3d<T> oy;
		static line_3d<T> oz;


		p_t pa;
		v_t v;


		p_t o() const { return pa; }


		line_3d()
			: pa(p_t::null)
			, v(v_t::null)
		{
		}

		line_3d(const p_t &pa, const p_t &pb)
			: pa(pa)
			, v((pb - pa).norm())
		{
		}

		explicit
		line_3d(const v_t &v)
			: pa(p_t::o)
			, v(v)
		{
		}

		line_3d(const p_t &pa, const v_t &v)
			: pa(pa)
			, v(v)
		{
		}

		line_3d(const line_3d &c)
			: pa(c.pa)
			, v(c.v)
		{
		}

		template <typename U>
		explicit line_3d(const line_3d<U> &c)
			: pa(c.pa)
			, v(c.v)
		{
		}
	};



	template <typename T>
	struct ray_3d : public line_3d<T>
	{
		INHERIT_BASIS(line_3d<T>);


		using line_3d<T>::pa;
		v_t d;


		p_t o() const { return pa; }
	};



	template <typename T>
	struct line_segment_3d : public line_3d<T>
	{
		INHERIT_BASIS(line_3d<T>);


		using line_3d<T>::pa;
		p_t pb;


		p_t o() const { return median(pa, pb); }


		line_segment_3d(const p_t &pa, const p_t &pb)
			: line_3d<T>(pa, pb)
			, pb(pb)
		{
		}

		line_segment_3d(const line_segment_3d &c)
			: line_3d<T>(c)
			, pb(c.pb)
		{
		}

		template <typename U>
		explicit line_segment_3d(const line_segment_3d<U> &c)
			: line_3d<T>(c)
			, pb(c.pb)
		{
		}


		p_t operator [](f_t dl) const
		{
			return p_t(pa + (pb - pa) * dl);
		}

		f_t operator [](const p_t &p) const // DEFECT not so fast
		{
			T t = 0;
			int n = 0;

			if (ne(pa.x, pb.x)) {
				t += (p.x - pa.x) / (pb.x - pa.x);
				n++;
			}
			if (ne(pa.y, pb.y)) {
				t += (p.y - pa.y) / (pb.y - pa.y);
				n++;
			}
			if (ne(pa.z, pb.z)) {
				t += (p.z - pa.z) / (pb.z - pa.z);
				n++;
			}

			return t/n;
		}
	};



	template <typename T, size_t S>
	struct poly_line_3d : public _base_line_3d<T>
	{
		INHERIT_BASIS(_base_line_3d<T>);


		p_t p[S];
		f_t u[S];


		p_t o() const { return median<S>(p); }


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
			return line_segment_3d<T>(p[i - 1], p[i])[dl - u[i-1]];
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
				r.z += p[i].z * w[i];
			}

			return r;
		}
	};

	template <size_t S, typename T, template <typename> class L>
	poly_line_3d<T, S> approximate(const L<T> &l)
	{
		poly_line_3d<T, S> npl;

		return npl;
	}

	template <size_t S, typename L>
	poly_line_3d<typename L::t_t, S> approximate(const L &l)
	{
		poly_line_3d<typename L::t_t, S> npl;

		return npl;
	}



	template <typename T/*, size_t S*/>
	struct bezier_line_3d : public poly_line_3d<T, 4/*S*/>
	{
		typedef poly_line_3d<T, 4/*S*/> _t;
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
	struct bspline_line_3d : public poly_line_3d<T, S>
	{
		typedef poly_line_3d<T, S> _t;
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
	struct dynamic_poly_line_3d : public _base_line_3d<T>
	{
		INHERIT_BASIS(_base_line_3d<T>);


		std::vector<p_t> p;
		std::vector<f_t> u;


		p_t o() const { return median<t_t>(p.begin(), p.end()); }


		dynamic_poly_line_3d(size_t s)
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
			return line_segment_3d<T>(p[i - 1], p[i])[dl - u[i-1]];
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
				r.z += p[i].z * w[i];
			}

			return r;
		}
	};

	template <typename T, template <typename> class L>
	dynamic_poly_line_3d<T> approximate(const L<T> &l, int s)
	{
		dynamic_poly_line_3d<T> npl(s);

		return npl;
	}

	template <typename L>
	dynamic_poly_line_3d<typename L::t_t> approximate(const L &l, int s)
	{
		dynamic_poly_line_3d<typename L::t_t> npl(s);

		return npl;
	}
}

#endif // math_lines_3d_h
