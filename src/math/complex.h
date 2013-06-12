#ifndef math_complex_h
#define math_complex_h

#include "fwd.h"

#include "primitives.h"

#include <complex>


namespace math
{
	template <typename T>
	struct complex : public std::complex<T>
	{
		complex()
			: std::complex<T>(1, 0)
		{
		}

		complex(T angle)
			: std::complex<T>(std::cos(angle), std::sin(angle))
		{
		}
	
		complex(T r, T i)
			: std::complex<T>(r, i)
		{
		}

		complex(const std::complex<T> &c)
			: std::complex<T>(c)
		{
		}


		T a() const { return this->real(); }
		T b() const { return this->imag(); }


		bool is_scalar() const
		{
			return this->a() == 0;
		}
	};

	template <typename T>
	inline
		complex<T>
		operator -(const complex<T> &c)
	{
		return complex<T>(c.a(), -c.b());
	}
}

#endif // math_complex_h
