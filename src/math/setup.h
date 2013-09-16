#ifndef math_setup_h
#define math_setup_h

#include "fwd.h"

#include "tuple.h"
#include "range.h"

#include "color.h"
#include "primitives.h"
#include "lines.h"
#include "figures.h"

#include "complex.h"
#include "quaternion.h"
#include "matrix.h"

#include "coordinate_system.h"



namespace math
{
	typedef float math_t;

	typedef tuple4_t<math_t> tuple4;
	
	typedef point_2d_t<math_t> point2;
	typedef vector_2d_t<math_t> vec2;
	typedef point_3d_t<math_t> point3;
	typedef vector_3d_t<math_t> vec3;

	typedef point_2d_t<math_t> point_2d;
	typedef vector_2d_t<math_t> vector_2d;
	typedef vector_2d_t<size_t> size_2d;
	typedef point_3d_t<math_t> point_3d;
	typedef vector_3d_t<math_t> vector_3d;
	typedef vector_2d_t<size_t> size_3d;

	typedef quaternion<math_t> quaternion_t;
	typedef matrix<math_t, 3> matrix_2d;
	typedef matrix<math_t, 4> matrix_3d;

	typedef line_t<point_2d> line_2d;
	typedef ray_t<point_2d> ray_2d;
	typedef line_segment_t<point_2d> line_segment_2d;
	//typedef poly_line_2d<math_t> poly_line_2d_t;

	typedef line_t<point_3d> line_3d;
	typedef ray_t<point_3d> ray_3d;
	typedef line_segment_t<point_3d> line_segment_3d;
	//typedef poly_line_3d<math_t> poly_line_3d_t;

	typedef aabb_t<point_2d> aabb_2d;
	typedef aabb_t<point_2d_t<size_t>> rect_2d;
	typedef triangle_t<point_2d> triangle_2d;
	typedef circle_t<point_2d> circle;

	typedef velocity_2d_t<math_t> velocity_2d;
	typedef acceleration_2d_t<math_t> acceleration_2d;

	typedef range_t<std::size_t> range;


#ifndef __clean__

	typedef plane<math_t> plane_t;
	typedef aabb_3d<math_t> aabb_3d_t;
	typedef triangle_t<point_3d> triangle_3d;
	typedef circle_t<point_3d> sphere;

	typedef complex<math_t> complex_t;
	typedef matrix<math_t, 3> matrix_2d_t;
	typedef matrix<math_t, 4> matrix_3d_t;

#endif

	typedef color_t<float> color;


	typedef velocity_2d vel2;
	typedef acceleration_2d acc2;
}



namespace math
{
	template <typename T> point_2d_t<T> point_2d_t<T>::o;
	template <typename T> point_2d_t<T> point_2d_t<T>::null;

	template <typename T> vector_2d_t<T> vector_2d_t<T>::o;
	template <typename T> vector_2d_t<T> vector_2d_t<T>::null;


	template <typename T> point_3d_t<T> point_3d_t<T>::o;
	template <typename T> point_3d_t<T> point_3d_t<T>::null;

	template <typename T> vector_3d_t<T> vector_3d_t<T>::o;
	template <typename T> vector_3d_t<T> vector_3d_t<T>::null;


	template <typename P> line_segment_t<P> line_segment_t<P>::null;

	template <typename P> aabb_t<P> aabb_t<P>::o;
	template <typename P> aabb_t<P> aabb_t<P>::null;


	template <typename T> color_t<T> color_t<T>::black;
	template <typename T> color_t<T> color_t<T>::white;

	template <typename T> color_t<T> color_t<T>::red;
	template <typename T> color_t<T> color_t<T>::green;
	template <typename T> color_t<T> color_t<T>::blue;

	template <typename T> color_t<T> color_t<T>::yellow;
	template <typename T> color_t<T> color_t<T>::olive;
	template <typename T> color_t<T> color_t<T>::magenta;
	template <typename T> color_t<T> color_t<T>::purple;
	template <typename T> color_t<T> color_t<T>::cyan;
	template <typename T> color_t<T> color_t<T>::teal;
	template <typename T> color_t<T> color_t<T>::light_blue;
	template <typename T> color_t<T> color_t<T>::dark_blue;



	template <typename T>
	void setup()
	{
		point_2d_t<T>::null = point_2d_t<T>(basis<T>::nan(), basis<T>::nan());

		point_3d_t<T>::null = point_3d_t<T>(basis<T>::nan(), basis<T>::nan(), basis<T>::nan());


		line_segment_t<point_2d_t<T>>::null = line_segment_t<point_2d_t<T>>();
		line_segment_t<point_3d_t<T>>::null = line_segment_t<point_3d_t<T>>();


		aabb_t<point_2d_t<T>>::null = aabb_t<point_2d_t<T>>{ basis<T>::nan(), basis<T>::nan(), basis<T>::nan(), basis<T>::nan() };


		color_t<T>::black     = color_t<T>(basis<T>::min()
		                                 , basis<T>::min()
		                                 , basis<T>::min());
		color_t<T>::white     = color_t<T>(basis<T>::max()
		                                 , basis<T>::max()
		                                 , basis<T>::max());

		color_t<T>::red       = color_t<T>(basis<T>::max()
		                                 , basis<T>::min()
		                                 , basis<T>::min());
		color_t<T>::green     = color_t<T>(basis<T>::min()
		                                 , basis<T>::max()
		                                 , basis<T>::min());
		color_t<T>::blue      = color_t<T>(basis<T>::min()
		                                 , basis<T>::min()
		                                 , basis<T>::max());

		color_t<T>::yellow    = color_t<T>(basis<T>::max()
		                                 , basis<T>::max()
		                                 , basis<T>::min());
		color_t<T>::olive     = color_t<T>(basis<T>::max() / 2
		                                 , basis<T>::max() / 2
		                                 , basis<T>::min());
		color_t<T>::magenta   = color_t<T>(basis<T>::max()
		                                 , basis<T>::min()
		                                 , basis<T>::max());
		color_t<T>::purple    = color_t<T>(basis<T>::max() / 2
		                                 , basis<T>::min()
		                                 , basis<T>::max() / 2);
		color_t<T>::cyan      = color_t<T>(basis<T>::min()
		                                 , basis<T>::max()
		                                 , basis<T>::max());
		color_t<T>::teal      = color_t<T>(basis<T>::min()
		                                 , basis<T>::max()
		                                 , basis<T>::max());

		color_t<T>::light_blue;
		color_t<T>::dark_blue;


		coordinate_system<T>();
	}

	inline void setup() { math::setup<math_t>(); }

	inline math_t nan() { return basis<math_t>::nan(); }
}

#endif // math_setup_h
