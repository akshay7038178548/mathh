#ifndef math_position_h
#define math_position_h

#include "fwd.h"


namespace math
{
	struct position_t {
		enum v_t {
			outer = -1,

			inner = 1,
		} v;

		position_t(v_t v) : v(v) {}
		operator bool() const { return v < outer; }
	};

	template <typename T>
	position_t position(const point_2d_t<T> &p, const line_t<point_2d_t<T>> &l)
	{
		return position_t(position_t::outer);
	}
}


#endif // math_position_h
