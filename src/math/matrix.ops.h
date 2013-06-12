#ifndef math_matrix_ops_h
#define math_matrix_ops_h

#include "complex.h"
#include "matrix.h"
#include "quaternion.h"
#include "primitives.h"


namespace math
{
	template <typename T, size_t S>
	inline
		matrix<T, S> &identity(matrix<T, S> &m)
	{
		int i = 0;
		for (size_t c = 0; c < S; c++) {
			for (size_t r = 0; r < S; r++, i++) {
				m.m[i] = (r == c) ? basis<T>::one() : basis<T>::zero();
			}
		}
		return m;
	}

	template <typename T, size_t S>
	inline
		T determinant(const matrix<T, S> &m)
	{
		T d = basis<T>::zero();
		for (size_t c = 0; c < S; c++) {
			T dd = basis<T>::one();
			for (size_t r = 0; r < S; r++) {
				dd *= m(r, (c + r)%S);
			}
			d += dd;
		}
		for (size_t c = 0; c < S; c++) {
			T dd = basis<T>::one();
			for (size_t r = 0; r < S; r++) {
				dd *= m(S - r, (c + r)%S);
			}
			d -= dd;
		}
		return d;
	}

	template <typename T, size_t S>
	inline
		matrix<T, S> &transpose(matrix<T, S> &m)
	{
		for (size_t c = 0; c < S; c++) {
			for (size_t r = c+1; r < S; r++) {
				std::swap(m(r,c), m(c,r));
			}
		}

		return m;
	}

	template <typename T>
	inline
		matrix<T, 2> &inverse(matrix<T, 2> &m)
	{
		T d = determinant(m);

		std::swap(m(0, 0), m(1, 1));
		m(1, 0) = -m(1, 0);
		m(0, 1) = -m(0, 1);

		m *= 1/d;

		return m;
	}

	template <typename T>
	inline
		matrix<T, 3> &inverse(matrix<T, 3> &m)
	{
		T d = determinant(m);

		transpose(m);
		m *= 1/d;

		return m;
	}

	template <typename T>
	inline
		matrix<T, 4> &inverse(matrix<T, 4> &m)
	{
		throw 1;
		return m;
	}


	template <typename T>
	inline
		matrix<T, 4> &
		look(matrix<T, 4> &m, const point_3d_t<T> &o, const quaternion<T> &r)
	{
		T x = math_cast<T>(r.x());
		T y = math_cast<T>(r.y());
		T z = math_cast<T>(r.z());
		T w = math_cast<T>(r.w());
		T s = 2 * basis<T>::one();

		T x2 = x * s;
		T y2 = y * s;
		T z2 = z * s;

		T xx = x * x2;
		T yy = y * y2;
		T wx = w * x2;
		T xy = x * y2;
		T yz = y * z2;
		T wy = w * y2;
		T xz = x * z2;
		T zz = z * z2;
		T wz = w * z2;


		m(0,0) = basis<T>::one() - (yy + zz);
		m(1,0) = xy + wz;
		m(2,0) = xz - wy;

		m(0,1) = xy - wz;
		m(1,1) = basis<T>::one() - (xx + zz);
		m(2,1) = yz + wx;

		m(0,2) = xz + wy;
		m(1,2) = yz - wx;
		m(2,2) = basis<T>::one() - (xx + yy);



		m.m[12] = math_cast<T>(o.x);
		m.m[13] = math_cast<T>(o.y);
		m.m[14] = math_cast<T>(o.z);


		return m;
	}


	template <typename T>
	inline
		matrix<T, 4> &
		look(matrix<T, 4> &m, const vector_3d_t<T> &d, const vector_3d_t<T> &u = vector_3d_t<T>::up)
	{

		vector_3d_t<T> &ox = (vector_3d_t<T> &)m.m[0];
		vector_3d_t<T> &oy = (vector_3d_t<T> &)m.m[4];
		vector_3d_t<T> &oz = (vector_3d_t<T> &)m.m[8];

		oz = d;
		ox = u * oz;  ox.normalize();
		oy = oz * ox; oy.normalize();

		return m;
	}
	
	template <typename T>
	inline
		matrix<T, 4> &
		look(matrix<T, 4> &m, const point_3d_t<T> &o, const vector_3d_t<T> &d, const vector_3d_t<T> &u = vector_3d_t<T>::up)
	{
		vector_3d_t<T> &ox = (vector_3d_t<T> &)m.m[0];
		vector_3d_t<T> &oy = (vector_3d_t<T> &)m.m[4];
		vector_3d_t<T> &oz = (vector_3d_t<T> &)m.m[8];

		oz = d;
		ox = u * oz;  ox.normalize();
		oy = oz * ox; oy.normalize();

		translation_to_m(o, m);

		return m;
	}

	template <typename T> inline matrix<T, 4> look(const point_3d_t<T> &o, const quaternion<T> &r) { matrix<T, 4> m; look(m, o, r); return m; }

	template <typename T>
	inline
		matrix<T, 4> &
		orthographic(matrix<T, 4> &m, T width, T height, T znear, T zfar)
	{
		m.m[ 0] = 1 / width;
		m.m[ 1] = 0;
		m.m[ 2] = 0;
		m.m[ 3] = 0;

		m.m[ 4] = 0;
		m.m[ 5] = 1 / height;
		m.m[ 6] = 0;
		m.m[ 7] = 0;

		m.m[ 8] = 0;
		m.m[ 9] = 0;
		m.m[10] = -2 / (zfar-znear);
		m.m[11] = 0;

		m.m[12] = 0;
		m.m[13] = 0;
		m.m[14] = -(zfar+znear) / (zfar-znear);
		m.m[15] = 1;

		return m;
	}

	template <typename T>
	inline
		matrix<T, 4> &
		perespective(matrix<T, 4> &m, T fov, T aspect, T znear, T zfar)
	{
		T f = 1 / std::tan(fov/2);
		T A = (zfar+znear) / (znear-zfar);
		T B = (2*zfar*znear) / (znear-zfar);

		m.m[ 0] = f / aspect;
		m.m[ 1] = 0;
		m.m[ 2] = 0;
		m.m[ 3] = 0;

		m.m[ 4] = 0;
		m.m[ 5] = f;
		m.m[ 6] = 0;
		m.m[ 7] = 0;

		m.m[ 8] = 0;
		m.m[ 9] = 0;
		m.m[10] = A;
		m.m[11] = -1;

		m.m[12] = 0;
		m.m[13] = 0;
		m.m[14] = B;
		m.m[15] = 0;

		return m;
	}


	// _2D

	template <typename T>
	inline
		matrix<T, 3> projection(const point_2d_t<T> &a, const point_2d_t<T> &b)
	{
		T d[] = {
			b.x - a.x, b.y - a.y, 0,
			a.y - b.y, a.x - b.x, 0,
			        0,         0, 1,
		};
		return matrix<T, 3>(d);
	}

	template <typename T>
	inline
		matrix<T, 3> projection(const point_2d_t<T> &o, const vector_2d_t<T> &d)
	{
		return projection(o, o + d);
	}

	template <typename T, typename U>
	inline
		point_2d_t<U>
		operator *(const matrix<T, 3> &l, const point_2d_t<U> &p)
	{
#define rc(r, c) m[r + c*3]

		U w = l.rc(2,0)*p.x + l.rc(2,1)*p.y + l.m[8];
		point_2d_t<U> mp((math_cast<U>(l.rc(0,0)*p.x + l.rc(0,1)*p.y + l.m[6])/w)
		               , (math_cast<U>(l.rc(1,0)*p.x + l.rc(1,1)*p.y + l.m[7])/w));

#undef rc

		return mp;
	}

	template <typename T, typename U>
	inline
		vector_2d_t<U>
		operator *(const matrix<T, 3> &l, const vector_2d_t<U> &v)
	{
#define rc(r, c) m[r + c*3]

		return vector_2d_t<U>(math_cast<U>(l.rc(0,0)*v.x + l.rc(0,1)*v.y)
		                    , math_cast<U>(l.rc(1,0)*v.x + l.rc(1,1)*v.y));

#undef rc
	}

#if 0

	template <typename T, typename U>
	inline
		math2d::aabb<U>
		operator *(const matrix<T, 3> &l, const math2d::aabb<U> &d)
	{
		return math2d::aabb<U>(l * d.o(), d.v()/*TODO: scale v.*/);
	}

	template <typename T, typename U>
	inline
		math2d::circle<U>
		operator *(const matrix<T, 3> &l, const math2d::circle<U> &c)
	{
		return math2d::circle<T>(l * c.o(), c.r/*TODO: scale r.*/);
	}

#endif

	template <typename T, typename U>
	inline
		matrix<U, 3> &
		rotation_to_m(const complex<T> &c, matrix<U, 3> &m)
	{

#define rc(r, c) m[r + c*3]

		m.rc(0,0) = c.a();
		m.rc(1,0) = c.b();

		m.rc(0,1) = -c.b();
		m.rc(1,1) = c.a();

#undef rc

		return m;
	}

	template <typename T, typename U>
	inline
		matrix<U, 3> &
		translation_to_m(const _base_primitive_2d<T> &v, matrix<U, 3> &m)
	{
		m.m[6] = math_cast<U>(v.x);
		m.m[7] = math_cast<U>(v.y);

		return m;
	}



	// _3D

	template <typename T, typename U>
	inline
		point_3d_t<U>
		operator *(const matrix<T, 4> &l, const point_3d_t<U> &p)
	{
#define rc(r, c) m[r + c*4]

		U w = l.rc(3,0)*p.x + l.rc(3,1)*p.y + l.rc(3,2)*p.z + l.m[15];
		return point_3d_t<U>((math_cast<U>(l.rc(0,0)*p.x + l.rc(0,1)*p.y + l.rc(0,2)*p.z + l.m[12])/w)
		                    , (math_cast<U>(l.rc(1,0)*p.x + l.rc(1,1)*p.y + l.rc(1,2)*p.z + l.m[13])/w)
		                    , (math_cast<U>(l.rc(2,0)*p.x + l.rc(2,1)*p.y + l.rc(2,2)*p.z + l.m[14])/w));

#undef rc
	}

	template <typename T, typename U>
	inline
		vector_3d_t<U>
		operator *(const matrix<T, 4> &l, const vector_3d_t<U> &v)
	{
#define rc(r, c) m[r + c*4]

		return vector_3d_t<U>(math_cast<U>(l.rc(0,0)*v.x + l.rc(0,1)*v.y + l.rc(0,2)*v.z)
		                       , math_cast<U>(l.rc(1,0)*v.x + l.rc(1,1)*v.y + l.rc(1,2)*v.z)
		                       , math_cast<U>(l.rc(2,0)*v.x + l.rc(2,1)*v.y + l.rc(2,2)*v.z));

#undef rc
	}

#if 0

	template <typename T, typename U>
	inline
		math3d::aabb<U>
		operator *(const matrix<T, 4> &l, const math3d::aabb<U> &d)
	{
		return math3d::aabb<U>(l * d.o(), d.v()/*TODO: scale v.*/);
	}

	template <typename T, typename U>
	inline
		math3d::sphere<U>
		operator *(const matrix<T, 4> &l, const math3d::sphere<U> &s)
	{
		return math3d::sphere<U>(l * s.o(), s.r/*TODO: scale r.*/);
	}

	template <typename T, typename U>
	inline
		math3d::plane<U>
		operator *(const matrix<T, 4> &l, const math3d::plane<U> &p)
	{
		return math3d::plane<U>(l * p.o(), l * p.n);
	}

#endif


	/*
	template <typename T>
	static matrix<T, 4> operator *(const matrix<T, 4> &a, const matrix<T, 4> &b)
	{
		matrix<T, 4> m;

#define rc(r, c) m[r + c*4]

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				m.rc(r,c) = basis<T>::zero();
				for (int n = 0; n < 4; n++) {
					m.rc(r,c) += a.rc(r,n)*b.rc(n,c);
				}
			}
		}

#undef rc

		return m;
	}
	*/

/*
	template <typename T>
	matrix<T, 4> to_matrix(const quaternion<T> &q)
	{
		matrix<T, 
	}
*/

	template <typename T, typename U>
	matrix<U, 4> &rotation_to_m(const quaternion<T> &q, matrix<U, 4> &m)
	{
		U x = math_cast<U>(q.x());
		U y = math_cast<U>(q.y());
		U z = math_cast<U>(q.z());
		U w = math_cast<U>(q.w());
		U s = 2 * basis<U>::one();

		U x2 = x * s;
		U y2 = y * s;
		U z2 = z * s;

		U xx = x * x2;
		U yy = y * y2;
		U wx = w * x2;
		U xy = x * y2;
		U yz = y * z2;
		U wy = w * y2;
		U xz = x * z2;
		U zz = z * z2;
		U wz = w * z2;

#define rc(r, c) m[r + c*4]

		m.rc(0,0) = basis<U>::one() - (yy + zz);
		m.rc(1,0) = xy + wz;
		m.rc(2,0) = xz - wy;

		m.rc(0,1) = xy - wz;
		m.rc(1,1) = basis<U>::one() - (xx + zz);
		m.rc(2,1) = yz + wx;

		m.rc(0,2) = xz + wy;
		m.rc(1,2) = yz - wx;
		m.rc(2,2) = basis<U>::one() - (xx + yy);

#undef rc

		return m;
	}

	template <typename T, typename U>
	inline
		matrix<U, 4> &
		translation_to_m(const _base_primitive_3d<T> &v, matrix<U, 4> &m)
	{
		m.m[12] = math_cast<U>(v.x);
		m.m[13] = math_cast<U>(v.y);
		m.m[14] = math_cast<U>(v.z);

		return m;
	}

	template <typename T>
	inline
	matrix<T, 4> &rotate(const quaternion<T> &r, matrix<T, 4> &m)
	{
		matrix<T, 4> rm; rotation_to_m(r, rm);
		m = rm*m;
		return m;
	}

	template <typename T>
	inline
	matrix<T, 4> &translate(const _base_primitive_3d<T> &t, matrix<T, 4> &m)
	{
		matrix<T, 4> tm; translation_to_m(t, tm);
		m = tm*m;
		return m;
	}
	
	template <typename T>
	inline
	matrix<T, 4> coordinate_space(const vector_3d_t<T> &t, const vector_3d_t<T> &x, const vector_3d_t<T> &y, const vector_3d_t<T> &z)
	{
		return matrix<T, 4>(t, x, y, z);
	}
	
	template <typename T>
	inline
	matrix<T, 4> make_coordinate_space(const vector_3d_t<T> &t)
	{
		return matrix<T, 4>(t, vector_3d::ox, vector_3d::oy, vector_3d::oz);
	}

	template <typename T>
	inline
	matrix<T, 4> make_coordinate_space_tuf(const vector_3d_t<T> &t, const vector_3d_t<T> &u, const vector_3d_t<T> &f)
	{
		return coordinate_space<T>(t, u * f, u, f);
	}
}

#endif // math_matrix_ops_h
