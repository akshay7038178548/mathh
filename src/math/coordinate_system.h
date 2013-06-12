#ifndef math_coordinate_system_h
#define math_coordinate_system_h

#include "fwd.h"

#include "primitives.h"


namespace math
{
	template <typename T> vector_2d_t<T> vector_2d_t<T>::ox;
	template <typename T> vector_2d_t<T> vector_2d_t<T>::oy;

	template <typename T> vector_2d_t<T> vector_2d_t<T>::right;
	template <typename T> vector_2d_t<T> vector_2d_t<T>::left;
	template <typename T> vector_2d_t<T> vector_2d_t<T>::up;
	template <typename T> vector_2d_t<T> vector_2d_t<T>::down;


	template <typename T> vector_3d_t<T> vector_3d_t<T>::ox;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::oy;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::oz;

	template <typename T> vector_3d_t<T> vector_3d_t<T>::right;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::left;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::forward;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::backward;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::up;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::down;


	template <typename P> ray_t<P> ray_t<P>::ox;
	template <typename P> ray_t<P> ray_t<P>::oy;
	template <typename P> ray_t<P> ray_t<P>::oz;

	template <typename T> plane<T> plane<T>::ox;
	template <typename T> plane<T> plane<T>::oy;
	template <typename T> plane<T> plane<T>::oz;




	template <typename T>
	void coordinate_system()
	{
		vector_2d_t<T>::ox = vector_2d_t<T>(basis<T>::one(), basis<T>::zero());
		vector_2d_t<T>::oy = vector_2d_t<T>(basis<T>::zero(), basis<T>::one());

		vector_2d_t<T>::right = vector_2d_t<T>(vector_2d_t<T>::ox);
		vector_2d_t<T>::left = vector_2d_t<T>(-vector_2d_t<T>::right);
		vector_2d_t<T>::up = vector_2d_t<T>(vector_2d_t<T>::oy);
		vector_2d_t<T>::down = vector_2d_t<T>(-vector_2d_t<T>::up);


		vector_3d_t<T>::ox = vector_3d_t<T>(basis<T>:: one(), basis<T>::zero(), basis<T>::zero());
		vector_3d_t<T>::oy = vector_3d_t<T>(basis<T>::zero(), basis<T>:: one(), basis<T>::zero());
		vector_3d_t<T>::oz = vector_3d_t<T>(basis<T>::zero(), basis<T>::zero(), basis<T>:: one());

		vector_3d_t<T>::forward = vector_3d_t<T>(vector_3d_t<T>::oz);
		vector_3d_t<T>::backward = vector_3d_t<T>(-vector_3d_t<T>::forward);
		vector_3d_t<T>::left = vector_3d_t<T>(vector_3d_t<T>::ox);
		vector_3d_t<T>::right = vector_3d_t<T>(-vector_3d_t<T>::right);
		vector_3d_t<T>::up = vector_3d_t<T>(vector_3d_t<T>::oy);
		vector_3d_t<T>::down = vector_3d_t<T>(-vector_3d_t<T>::up);

		//ray_t<T>::ox = line_3d<T>(vector_3d_t<T>::ox);
		//ray_t<T>::oy = line_3d<T>(vector_3d_t<T>::oy);
		//ray_t<T>::oz = line_3d<T>(vector_3d_t<T>::oz);

		plane<T>::ox = plane<T>(vector_3d_t<T>::ox);
		plane<T>::oy = plane<T>(vector_3d_t<T>::oy);
		plane<T>::oz = plane<T>(vector_3d_t<T>::oz);
	}
}

#endif // math_coordinate_system_h
