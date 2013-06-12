#ifndef math_primitives_3d_h
#define math_primitives_3d_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct _base_primitive_3d : private _base_primitive_2d<T>
	{
		DECLARE_BASIS_3D(T);


		using _base_primitive_2d<T>::x;
		using _base_primitive_2d<T>::y;
		T z;


	protected:
		_base_primitive_3d()
			: _base_primitive_2d<T>()
			, z(0)
		{
		}

		_base_primitive_3d(T x, T y, T z)
			: _base_primitive_2d<T>(x, y)
			, z(z)
		{
		}

		explicit
		_base_primitive_3d(const T *d)
			: _base_primitive_2d<T>(d)
			, z(d[2])
		{
		}

		template <typename U>
		_base_primitive_3d(U x, U y, U z)
			: _base_primitive_2d<T>(x, y)
			, z(math_cast<T>(z))
		{
		}

		_base_primitive_3d(const _base_primitive_3d<T> &c)
			: _base_primitive_2d<T>(c)
			, z(c.z)
		{
		}

		template <typename U>
		_base_primitive_3d(const _base_primitive_3d<U> &c)
			: _base_primitive_2d<T>(math_cast<T>(c.x), math_cast<T>(c.y))
			, z(math_cast<T>(c.z))
		{
		}
	};



	template <typename T>
	struct point_3d_t : public _base_primitive_3d<T>
	{
		INHERIT_BASIS(_base_primitive_3d<T>);


		static point_3d_t<T> o;
		static point_3d_t<T> null;


		point_3d_t sz(T z_) const { return point_3d_t(x, y, z_); }


		point_3d_t()
			: b_t()
		{
		}

		point_3d_t(T x, T y, T z)
			: b_t(x, y, z)
		{
		}


		explicit
		point_3d_t(const T *d)
			: b_t(d)
		{
		}

		point_3d_t(std::initializer_list<T> d)
			: b_t(d.begin())
		{
		}

		template <typename U>
		point_3d_t(U x, U y, U z)
			: b_t(x, y, z)
		{
		}

		point_3d_t(const point_3d_t &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		point_3d_t(const _base_primitive_3d<U> &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		point_3d_t(const point_2d_t<U> &c)
			: b_t(math_cast<T>(c.x), math_cast<T>(c.y), basis<T>::one())
		{
		}

		const point_2d_t<T> &
			as_2d() const
		{
			return reinterpret_cast<const point_2d_t<T> &>(*this);
		}

		point_2d_t<T> &
			as_2d()
		{
			return reinterpret_cast<point_2d_t<T> &>(*this);
		}
	};


	template <typename T>
	point_3d_t<T> make_p(T x, T y, T z)
	{
		return point_3d_t<T>(x, y, z);
	}



	template <typename T>
	struct vector_3d_t : public _base_primitive_3d<T>
	{
		INHERIT_BASIS(_base_primitive_3d<T>);


		static vector_3d_t<T> o;
		static vector_3d_t<T> null;

		static vector_3d_t<T> ox;
		static vector_3d_t<T> oy;
		static vector_3d_t<T> oz;

		static vector_3d_t<T> right;
		static vector_3d_t<T> left;
		static vector_3d_t<T> forward;
		static vector_3d_t<T> backward;
		static vector_3d_t<T> up;
		static vector_3d_t<T> down;


		vector_3d_t sz(T z_) const { return vector_3d_t(x, y, z_); }


		vector_3d_t()
			: b_t()
		{
		}

		vector_3d_t(T x, T y, T z)
			: b_t(x, y, z)
		{
		}

		template <typename U>
		vector_3d_t(U x, U y, U z)
			: b_t(x, y, z)
		{
		}

		vector_3d_t(const vector_3d_t &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		vector_3d_t(const _base_primitive_3d<U> &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		vector_3d_t(const vector_2d_t<U> &c)
			: b_t(math_cast<T>(c.x), math_cast<T>(c.y), basis<T>::zero())
		{
		}


		static vector_3d_t<T> norm(T x, T y, T z)
		{
			return vector_3d_t<T>(x, y, z).norm();
		}


		template <typename U>
		bool operator <(const vector_3d_t<U> &r) const
		{
			return (this->z < r.z)
			    || ((this->z == r.z) && ((this->y < r.y)
			                          || (this->y == r.y && this->x < r.x)));
		}


		T magnitude() const
		{
			return (this->x)*(this->x)
			     + (this->y)*(this->y)
			     + (this->z)*(this->z);
		}

		T length() const
		{
			return std::sqrt(magnitude());
		}


		vector_3d_t<T> norm() const
		{
			return (*this) / length();
		}

		vector_3d_t<T> &normalize()
		{
			return (*this) /= length();
		}
	};


	template <typename T>
	vector_3d_t<T> make_v(T x, T y, T z)
	{
		return vector_3d_t<T>(x, y, z);
	}

	template <typename T>
	vector_3d_t<T> normalize(vector_3d_t<T> v)
	{
		return v.norm();
	}

}

#endif // math_primitives_3d_h
