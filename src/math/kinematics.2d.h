#ifndef math_kinematics_2d_h
#define math_kinematics_2d_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct velocity_2d_t : public _base_primitive_2d<T>
	{
		INHERIT_BASIS(_base_primitive_2d<T>);


	public:
		velocity_2d_t()
		{
		}

		explicit
		velocity_2d_t(const _base_primitive_2d<T> &v)
			: b_t(v)
		{
		}


	public:
		v_t operator()(/*T dt = 1*/) const
		{
			return v_t(*this);
		}

		v_t operator()(T dt) const
		{
			return v_t(*this) * dt;
		}
	};

	template <typename T>
	struct acceleration_2d_t : public _base_primitive_2d<T>
	{
		INHERIT_BASIS(_base_primitive_2d<T>);


	public:
		acceleration_2d_t()
		{
		}

		explicit
		acceleration_2d_t(const v_t &v)
			: b_t(v)
		{
		}


	public:
		velocity_2d_t<T> operator()(/*T dt = 1*/) const
		{
			return velocity_2d_t<T>((*this));
		}

		velocity_2d_t<T> operator()(T dt) const
		{
			return velocity_2d_t<T>(*this) * dt;
		}
	};
}

#endif // math_kinematics_2d_h
