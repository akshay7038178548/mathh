#ifndef math_primitives_2d_h
#define math_primitives_2d_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct _base_primitive_2d
	{
		DECLARE_BASIS_2D(T);


		T x;
		T y;


	protected:
		_base_primitive_2d()
			: x(0)
			, y(0)
		{
		}

		_base_primitive_2d(T x, T y)
			: x(x)
			, y(y)
		{
		}

		explicit
		_base_primitive_2d(const T *d)
			: x(d[0])
			, y(d[1])
		{
		}

		template <typename U>
		_base_primitive_2d(U x, U y)
			: x(math_cast<T>(x))
			, y(math_cast<T>(y))
		{
		}

		_base_primitive_2d(const _base_primitive_2d<T> &c)
			: x(c.x)
			, y(c.y)
		{
		}

		template <typename U>
		_base_primitive_2d(const _base_primitive_2d<U> &c)
			: x(math_cast<T>(c.x))
			, y(math_cast<T>(c.y))
		{
		}
	};



	template <typename T>
	struct point_2d_t : public _base_primitive_2d<T>
	{
		INHERIT_BASIS(_base_primitive_2d<T>);


		static point_2d_t<T> o;
		static point_2d_t<T> null;


		point_2d_t()
			: b_t()
		{
		}

		point_2d_t(T x, T y)
			: b_t(x, y)
		{
		}

		point_2d_t(std::initializer_list<T> d)
			: b_t(d.begin())
		{
		}

		template <typename U>
		point_2d_t(U x, U y)
			: b_t(x, y)
		{
		}

		point_2d_t(const point_2d_t &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		point_2d_t(const _base_primitive_2d<U> &c)
			: b_t(c)
		{
		}

		point_2d_t flip_x() const { return point_2d_t(-this->x,  this->y); }
		point_2d_t flip_y() const { return point_2d_t( this->x, -this->y); }
	};


	template <typename T>
	point_2d_t<T> make_p(T x, T y)
	{
		return point_2d_t<T>(x, y);
	}



	template <typename T>
	struct vector_2d_t : public _base_primitive_2d<T>
	{
		INHERIT_BASIS(_base_primitive_2d<T>);


		static vector_2d_t<T> o;
		static vector_2d_t<T> null;

		static vector_2d_t<T> ox;
		static vector_2d_t<T> oy;

		static vector_2d_t<T> right;
		static vector_2d_t<T> left;
		static vector_2d_t<T> up;
		static vector_2d_t<T> down;


		vector_2d_t()
			: b_t()
		{
		}

		vector_2d_t(T x, T y)
			: b_t(x, y)
		{
		}

		template <typename U>
		vector_2d_t(U x, U y)
			: b_t(x, y)
		{
		}

		vector_2d_t(const vector_2d_t &c)
			: b_t(c)
		{
		}

		template <typename U>
		explicit
		vector_2d_t(const _base_primitive_2d<U> &c)
			: b_t(c)
		{
		}

		vector_2d_t flip_x() const { return vector_2d_t(-this->x,  this->y); }
		vector_2d_t flip_y() const { return vector_2d_t( this->x, -this->y); }


		T magnitude() const
		{
			return (this->x)*(this->x)
			     + (this->y)*(this->y);
		}

		T length() const
		{
			return std::sqrt(magnitude());
		}


		vector_2d_t norm() const
		{
			return (*this) / length();
		}

		vector_2d_t &normalize()
		{
			return (*this) /= length();
		}

		vector_2d_t ort() const
		{
			return vector_2d_t(this->y, -this->x);
		}
	};


	template <typename T>
	vector_2d_t<T> make_v(T x, T y)
	{
		return vector_2d_t<T>(x, y);
	}
}

#endif // math_primitives_2d_h
