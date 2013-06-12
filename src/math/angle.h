#ifndef math_angle_h
#define math_angle_h

#include "fwd.h"


namespace math
{
	template <typename T>
	T angle(const vector_2d_t<T> &a)
	{
		return (((vector_2d_t<T>::ox % a) + 1)/2) * (vector_3d_t<T>(vector_2d_t<T>::ox) * vector_3d_t<T>(a)).z;
	}

	template <typename T>
	T angle(const vector_2d_t<T> &a, const vector_2d_t<T> &b)
	{
		return (((b % a) + 1)/2) * (vector_3d_t<T>(b) * vector_3d_t<T>(a)).z;
	}
}


#endif//math_angle_h
