#ifndef math_figures_3d_h
#define math_figures_3d_h

#include "primitives.3d.h"
#include "lines.h"

#include "figures.2d.h"


namespace math
{
	template <typename T>
	struct _base_figure_3d
	{
		DECLARE_BASIS_3D(T);


		virtual p_t o() const = 0;
//		virtual v_t n() const = 0;


		_base_figure_3d()
		{
		}

		_base_figure_3d(const _base_figure_3d &c)
		{
		}

		template <typename U>
		explicit _base_figure_3d(const _base_figure_3d<U> &c)
		{
		}
	};



	template <typename T>
	struct plane : public _base_figure_3d<T>
	{
		INHERIT_BASIS(_base_figure_3d<T>);


		static plane<T> ox;
		static plane<T> oy;
		static plane<T> oz;


		T p[4];
		T &a;
		T &b;
		T &c;
		T &d;


		p_t o() const
		{
			if (p[0] != 0) {
				return p_t(-p[3]/p[0], 0, 0);
			}
			if (p[1] != 0) {
				return p_t(0, -p[3]/p[1], 0);
			}
			if (p[2] != 0) {
				return p_t(0, 0, -p[3]/p[2]);
			}

			return p_t();
		}

		v_t n() const
		{
			return v_t(a, b, c);
		}


		plane()
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			p[0] = p[1] = p[2] = p[3] = basis<T>::nan();
		}

		plane(const v_t &nv)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			_init(p_t::o, nv);
		}

		plane(const p_t &o, const v_t &nv)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			_init(o, nv);
		}

		plane(const p_t &o, const v_t &a, const v_t &b)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			_init(o, (a * b).norm());
		}

		plane(const p_t &a, const p_t &b, const p_t &c)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			_init(a, ((b - a) * (c - a)).norm());
		}

		plane(const plane &c)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			std::memcpy(p, c.p, 4 * sizeof(T));
		}

		template <typename U>
		explicit plane(const plane<U> &c)
			: a(p[0])
			, b(p[1])
			, c(p[2])
			, d(p[3])
		{
			p[0] = math_cast<T>(c.p[0]);
			p[1] = math_cast<T>(c.p[1]);
			p[2] = math_cast<T>(c.p[2]);
			p[3] = math_cast<T>(c.p[3]);
		}

		plane &operator =(const plane &r)
		{
			std::memcpy(p, r.p, 4 * sizeof(T));
			return *this;
		}


		point_2d_t<T> project(const p_t &p) const
		{
			typedef point_2d_t<T> p2_t;

			if (!is_zero(this->p[0])) {
				return p2_t(p.z, p.y);
			}
			if (!is_zero(this->p[1])) {
				return p2_t(p.x, p.z);
			}
			if (!is_zero(this->p[2])) {
				return p2_t(p.x, p.y);
			}

			throw std::domain_error("cant project on empty plane");
		}

	private:
		void _init(const p_t &o, const v_t &nv)
		{
			p[0] = nv.x;
			p[1] = nv.y;
			p[2] = nv.z;
			p[3] = - (nv % (const v_t &)o);
		}
	};


	template <typename T>
	static plane<T> operator -(const plane<T> &l);


	template <typename T>
	static plane<T> &operator +=(plane<T> &l, T r);

	template <typename T>
	static plane<T> &operator -=(plane<T> &l, T r);


	template <typename T>
	static plane<T> operator +(const plane<T> &l, T r);

	template <typename T>
	static plane<T> operator -(const plane<T> &l, T r);



	template <typename T, typename B>
	struct face : public plane<T>
	{
		B b;

		face(const plane<T> &p, const B &b)
			: plane<T>(p)
			, b(b)
		{
		}

		face(const face &c)
			: plane<T>(c)
			, b(c.b)
		{
		}

		template <typename U>
		explicit face(const face<U, B> &c)
			: plane<T>(c)
			, b(c.b)
		{
		}
	};



	enum FACES
	{
		F_LEFT  = 1<<0,
		F_DOWN  = 1<<1,
		F_BACK  = 1<<2,
		F_RIGHT = 1<<3,
		F_UP	= 1<<4,
		F_FRONT = 1<<5,
	};

	template <typename T>
	struct aabb_3d : public _base_figure_3d<T>
	{
		INHERIT_BASIS(_base_figure_3d<T>);
		typedef face<t_t, aabb_t<point_2d_t<T>>> face_t;
		typedef line_segment_t<p_t> edge_t;


		static const unsigned int size = 6;


		p_t a;
		p_t b;


		p_t o() const { return median(a, b); }
		T w() const { return b.x - a.x; }
		T h() const { return b.y - a.y; }
		T d() const { return b.z - a.z; }


		aabb_3d()
		{
		}

		aabb_3d(const p_t &d)
			: a(-d.x/2.f, -d.y/2.f, -d.z/2.f)
			, b( d.x/2.f,  d.y/2.f,  d.z/2.f)
		{
		}

		aabb_3d(const p_t &a, const p_t &b)
			: a(a)
			, b(b)
		{
		}

		aabb_3d(const p_t &o, const v_t &v)
			: a(o - v)
			, b(o + v)
		{
		}

		aabb_3d(const aabb_3d &c)
			: a(c.a)
			, b(c.b)
		{
		}

		template <typename U>
		explicit aabb_3d(const aabb_3d<U> &c)
			: a(c.a)
			, b(c.b)
		{
		}

		aabb_3d(const aabb_t<point_2d_t<T>> &c)
			: a(c.a)
			, b(c.b)
		{
		}


		bool is_face(int f) const
		{
			return bits(f) == 1;
		}

		bool is_edge(int f) const
		{
			return bits(f) == 2;
		}

		bool is_vertex(int f) const
		{
			return bits(f) == 3;
		}


		int face_index(const p_t &p, int pface = 0) const
		{
			T d = 0;
			int r = 0;

			if (p.x < a.x && !(pface & F_LEFT)) {
				r = F_LEFT;
				d = a.x - p.x;
			}
			if (p.y < a.y && !(pface & F_DOWN)) {
				if (a.y - p.y > d) {
					r = F_DOWN;
					d = a.y - p.y;
				}
			}
			if (p.z < a.z && !(pface & F_BACK)) {
				if (a.z - p.z > d) {
					r = F_BACK;
					d = a.z - p.z;
				}
			}
			if (p.x > b.x && !(pface & F_RIGHT)) {
				if (p.x - b.x > d) {
					r = F_RIGHT;
					d = p.x - b.x;
				}
			}
			if (p.y > b.y && !(pface & F_UP)) {
				if (p.y - b.y > d) {
					r = F_UP;
					d = p.y - b.y;
				}
			}
			if (p.z > b.z && !(pface & F_FRONT)) {
				if (p.z - b.z > d) {
					r = F_FRONT;
					d = p.z - b.z;
				}
			}

			return r;
		}

		face_t get_face(int ib) const
		{
			switch (ib) {
			case F_LEFT:  return face_t(plane<T>::ox + a.x, make_aabb(a.z, a.y, b.z, b.y)); // left
			case F_DOWN:  return face_t(plane<T>::oy + a.y, make_aabb(a.x, a.z, b.x, b.z)); // down
			case F_BACK:  return face_t(plane<T>::oz + a.z, make_aabb(a.x, a.y, b.x, b.y)); // back
			case F_RIGHT: return face_t(plane<T>::ox + b.x, make_aabb(a.z, a.y, b.z, b.y)); // right
			case F_UP:    return face_t(plane<T>::oy + b.y, make_aabb(a.x, a.z, b.x, b.z)); // up
			case F_FRONT: return face_t(plane<T>::oz + b.z, make_aabb(a.x, a.y, b.x, b.y)); // front
			}

			throw std::out_of_range("Face index out of range");
		}

		edge_t get_edge(int f) const
		{
			return edge_t(
				point_3d_t<T>((f & F_LEFT) ? a.x : (f & F_RIGHT) ? b.x : a.x
				            , (f & F_DOWN) ? a.y : (f & F_UP)    ? b.y : a.y
				            , (f & F_BACK) ? a.z : (f & F_FRONT) ? b.z : a.z)
			  , point_3d_t<T>((f & F_LEFT) ? a.x : (f & F_RIGHT) ? b.x : b.x
				            , (f & F_DOWN) ? a.y : (f & F_UP)    ? b.y : b.y
				            , (f & F_BACK) ? a.z : (f & F_FRONT) ? b.z : b.z));
		}

		p_t get_vertex(int f) const
		{
			return p_t((f & F_LEFT) ? a.x : b.x
			         , (f & F_DOWN) ? a.y : b.y
			         , (f & F_BACK) ? a.z : b.z);
		}
	};

	template<typename T, typename U>
	static aabb_3d<T> &operator +=(aabb_3d<T> &l, const vector_3d_t<U> &r);

	template<typename T, typename U>
	static aabb_3d<T> &operator -=(aabb_3d<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static aabb_3d<T> operator +(const aabb_3d<T> &l, const vector_3d_t<U> &r);

	template <typename T, typename U>
	static aabb_3d<T> operator -(const aabb_3d<T> &l, const vector_3d_t<U> &r);



	template <typename T>
	struct frustrum : public _base_figure_3d<T>
	{
		INHERIT_BASIS(_base_figure_3d<T>);


		plane<T> left_face;
		plane<T> right_face;
		plane<T> bottom_face;
		plane<T> top_face;
		plane<T> far_face;
		plane<T> near_face;


		p_t o() const { return p_t::o; }


		frustrum()
		{
		}

		frustrum(T fov, T aspect, T znear, T zfar)
			: far_face(p_t(0, 0, zfar), -v_t::oz)
			, near_face(p_t(0, 0, znear), v_t::oz)
		{
			T tng = std::tan(fov/2);
			p_t pnl = p_t(-tng*znear, 0, znear);
			p_t pfl = p_t(-tng*zfar, 0, zfar);
			v_t vl = pfl - pnl;

			v_t nl = v_t( vl.z, 0, -vl.x);
			v_t nr = v_t(-vl.z, 0, -vl.x);
			left_face = plane<T>(nl);
			right_face = plane<T>(nr);


			p_t pnb = p_t(0, -tng*znear/aspect, znear);
			p_t pfb = p_t(0, -tng*zfar/aspect, zfar);
			v_t vb = pfb - pnb;

			v_t nb = v_t(0,  vb.z, -vb.y);
			v_t nt = v_t(0, -vb.z, -vb.y);
			bottom_face = plane<T>(nb);
			top_face = plane<T>(nt);
		}
	};



	// _operator

	template <typename T>
	static plane<T> operator -(const plane<T> &l)
	{
		return plane<T>(l.o(), -l.n());
	}

	template <typename T>
	static plane<T> &operator +=(plane<T> &l, T r)
	{
		vector_3d_t<T> ro(l.o() + l.n() * r);
		l.p[3] = - (l.n() % ro);

		return l;
	}

	template <typename T>
	static plane<T> &operator -=(plane<T> &l, T r)
	{
		vector_3d_t<T> ro(l.o() - l.n() * r);
		l.p[3] = - (l.n() % ro);

		return l;
	}

	template <typename T>
	static plane<T> operator +(const plane<T> &l, T r)
	{
		return plane<T>(l.o() + l.n() * r, l.n());
	}

	template <typename T>
	static plane<T> operator -(const plane<T> &l, T r)
	{
		return plane<T>(l.o() - l.n() * r, l.n());
	}


	template <typename T, typename U>
	static aabb_3d<T> &operator +=(aabb_3d<T> &l, const vector_3d_t<U> &r)
	{
		l.a += r;
		l.b += r;

		return l;
	}

	template <typename T, typename U>
	static aabb_3d<T> &operator -=(aabb_3d<T> &l, const vector_3d_t<U> &r)
	{
		l.a -= r;
		l.b -= r;

		return l;
	}

	template <typename T, typename U>
	static aabb_3d<T> operator +(const aabb_3d<T> &l, const vector_3d_t<U> &r)
	{
		return aabb_3d<T>(l.a + r, l.b + r);
	}

	template <typename T, typename U>
	static aabb_3d<T> operator -(const aabb_3d<T> &l, const vector_3d_t<U> &r)
	{
		return aabb_3d<T>(l.a - r, l.b - r);
	}
}

/*
namespace math
{
	template <typename T>
	aabb_3d<T> add(const aabb_3d<T> &l, const vector_3d_t<T> &r)
	{
		aabb_3d<T> res(l); res += r;
		return res;
	}

	template <typename T>
	aabb_3d<T> sub(const aabb_3d<T> &l, const vector_3d_t<T> &r)
	{
		aabb_3d<T> res(l); res -= r;
		return res;
	}
}
*/

#endif // math_figures_3d_h
