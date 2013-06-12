#ifndef math_quaternion_h
#define math_quaternion_h

#include "fwd.h"

#include "primitives.h"

#include <boost/math/quaternion.hpp>


namespace math
{
	template <typename T>
	struct quaternion : public boost::math::quaternion<T>
	{
		static quaternion<T> ax15;
		static quaternion<T> ay15;
		static quaternion<T> az15;

		quaternion()
			: boost::math::quaternion<T>(1, 0, 0, 0)
		{
		}

		quaternion(const vector_3d_t<T> &v, T angle)
			: boost::math::quaternion<T>(0.f, v.x, v.y, v.z)
		{
			T ha = angle / 2.f;
			T sa = std::sin(ha);
			this->a = std::cos(ha); this->b *= sa; this->c *= sa; this->d *= sa;
			(*this) /= boost::math::abs(*this);
		}

		quaternion(T w, T x, T y, T z)
			: boost::math::quaternion<T>(w, x, y, z)
		{
		}

		quaternion(const boost::math::quaternion<T> &c)
			: boost::math::quaternion<T>(c)
		{
		}


		T w() const { return this->R_component_1(); }
		T x() const { return this->R_component_2(); }
		T y() const { return this->R_component_3(); }
		T z() const { return this->R_component_4(); }


		bool is_scalar() const
		{
			return x() == y() == z() == 0;
		}

		T magnitude() const
		{
			return boost::math::norm(*this);
		}

		T length() const
		{
			return boost::math::abs(*this);
		}


		quaternion<T> norm() const
		{
			return (*this) / length();
		}

		quaternion<T> &normalize()
		{
			(*this) /= boost::math::abs(*this);
			return *this;
		}
	};


	template <typename T>
	quaternion<T> quaternion<T>::ax15(vector_3d_t<T>::ox, 15 * degrees);

	template <typename T>
	quaternion<T> quaternion<T>::ay15(vector_3d_t<T>::oy, 15 * degrees);

	template <typename T>
	quaternion<T> quaternion<T>::az15(vector_3d_t<T>::oz, 15 * degrees);


	template <typename T>
	inline
	quaternion<T> operator -(const quaternion<T> &r)
	{
		return quaternion<T>(r.w(), -r.x(), -r.y(), -r.z());
	}

	template <typename T>
	inline
	quaternion<T> operator ^(const quaternion<T> &l, int r)
	{
		return boost::math::pow(l, r);
	}

#if 1
	template <typename T>
	inline
	vector_3d_t<T> operator ^(const quaternion<T> &l, const vector_3d_t<T> &v)
	{
		quaternion<T> r(l); r *= quaternion<T>(0, v.x, v.y, v.z) *= -l;
		return vector_3d_t<T>(r.x(), r.y(), r.z());
	}
#endif
}

#endif // math_quaternion_h
