#ifndef math_fwd_h
#define math_fwd_h

#include <cmath>
#include <cstring>

#include <deque>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include "constants.h"


#define math_cast static_cast

namespace math
{
	using std::abs;
	using std::cos;
	using std::sin;
	using std::acos;

	template <typename T> struct tuple4_t;

	template <typename T> struct array;
	template <typename T> class set_t;
	template <typename T> class graph_t;
	template <typename T> class mesh_t;
	template <typename T> class grid_t;


	template <typename T> struct color_t;
	template <typename T> struct color_hsl_t;
	template <typename T> struct color_hsv_t;


	template <typename T, size_t S> struct matrix;


	template <typename T> struct point_2d_t;
	template <typename T> struct vector_2d_t;

//	template <typename T> struct line_2d;
//	template <typename T> struct ray_2d;
//	template <typename T> struct line_segment_2d;
//	template <typename T, size_t S> struct poly_line_2d;

//	template <typename T> struct aabb_2d;

	//template <typename T> struct matrix_2d : public matrix<T, 3> { using matrix<T, 3>::matrix<T, 3>; };


	template <typename T> struct point_3d_t;
	template <typename T> struct vector_3d_t;

//	template <typename T> struct line_3d;
//	template <typename T> struct ray_3d;
//	template <typename T> struct line_segment_3d;
	template <typename T, size_t S> struct poly_line_3d;

	template <typename T> struct plane;
	template <typename T, typename B> struct face;
	template <typename T> struct aabb_3d;
	template <typename T> struct frustrum;


	template <typename P> struct line_t;
	template <typename P> struct ray_t;
	template <typename P> struct line_segment_t;
	template <typename P, size_t S> struct poly_line_t;
	template <typename P> struct dynamic_poly_line_t;
	template <typename P> struct aabb_t;
	template <typename P, size_t S> struct polygon_t;
	template <typename P> struct triangle_t;
	template <typename P> struct circle_t;

	//template <typename T> struct matrix_3d : public matrix<T, 4> { using matrix<T, 4>::matrix<T, 4>; };

	template <typename T> struct velocity_2d_t;
	template <typename T> struct acceleration_2d_t;
}

#include "basis.h"
#include "precision.h"

namespace math
{
	template <typename T>
	int bits(T t)
	{
		int c = 0;
		while (t) {
			c += (t & 1);
			t >>= 1;
		}
		return c;
	}

	template <typename T>
	struct math_tag {
		operator bool() const {
			return !math::is_null(*static_cast<const T *>(this));
		}
	};
}

#endif // math_fwd_h
