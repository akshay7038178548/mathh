#ifndef math_kinematics_2d_h
#define math_kinematics_2d_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct velocity_2d : protected vector_2d_t<T>
	{
		INHERIT_BASIS(vector_2d_t<T>);


	public:
		explicit
		velocity_2d(const v_t &v)
			: b_t(v)
		{
		}


	public:
		v_t operator()(/*T dt = 1*/) const
		{
			return (*this);
		}

		v_t operator()(T dt) const
		{
			return (*this) * dt;
		}
	};

	template <typename T>
	struct acceleration_2d : protected vector_2d_t<T>
	{
		INHERIT_BASIS(vector_2d_t<T>);


	public:
		explicit
		acceleration_2d(const v_t &v)
			: b_t(v)
		{
		}


	public:
		velocity_2d<T> operator()(/*T dt = 1*/) const
		{
			return velocity_2d<T>((*this));
		}

		velocity_2d<T> operator()(T dt) const
		{
			return velocity_2d<T>((*this) * dt);
		}
	};
}

#endif // math_kinematics_2d_h
