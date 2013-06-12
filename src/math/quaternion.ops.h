#ifndef math_quaternion_ops_h
#define math_quaternion_ops_h

#include "matrix.h"
#include "quaternion.h"


namespace math
{
	template <typename T>
	quaternion<T> &matrix_to_q(const matrix<T, 4> &m, quaternion<T> &q)
	{
		typedef quaternion<T> q_t;

#define mrc(c, r) m.m[r + c*4]

		float tr = mrc(0,0) + mrc(1,1) + mrc(2,2);
		if (tr > 0.f) {
			float w = tr + 1;
			q = q_t(w, mrc(1,2) - mrc(2,1), mrc(2,0) - mrc(0,2), mrc(0,1) - mrc(1,0));
			q *= (0.5f/std::sqrt(w));
		}
		else if ((mrc(0,0) > mrc(1,1)) && (mrc(0,0) > mrc(2,2))) {
			float x = 1 + mrc(0,0) - mrc(1,1) - mrc(2,2);
			q = q_t(mrc(1,2) - mrc(2,1), x, mrc(1,0) + mrc(0,1), mrc(2,0) + mrc(0,2));
			q *= (0.5f/std::sqrt(x));
		}
		else if (mrc(1,1) > mrc(2,2)) {
			float y = 1 + mrc(1,1) - mrc(0,0) - mrc(2,2);
			q = q_t(mrc(2,0) - mrc(0,2), mrc(1,0) + mrc(0,1), y, mrc(2,1) + mrc(1,2));
			q *= (0.5f/std::sqrt(y));
		}
		else {
			float z = 1 + mrc(2,2) - mrc(0,0) - mrc(1,1);
			q = q_t(mrc(0,1) - mrc(1,0), mrc(2,0) + mrc(0,2), mrc(2,1) + mrc(1,2), z);
			q *= (0.5f/std::sqrt(z));
		}

#undef mrc

		return q;
	}
}

#endif // math_quaternion_ops_h
