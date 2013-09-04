#ifndef math_precision_h
#define math_precision_h

#include "basis.h"


namespace math
{
	template <typename T> bool is_null(T a);
	template <typename T, template <typename> class P> bool is_null(const P<T> &p);
	template <typename T> bool is_zero(T a);
	template <typename T, template <typename> class P> bool is_zero(const P<T> &p);

	template <typename T> bool is_one(T a);

	template <typename T> bool eq(T a, T b);
	template <typename T> bool ne(T a, T b);
	template <typename T> bool gt(T a, T b);
	template <typename T> bool lt(T a, T b);
	template <typename T> bool gte(T a, T b);
	template <typename T> bool lte(T a, T b);

	template <typename T> bool aeq(T a, T b);



	template <typename T>
	bool is_null(T a)
	{
		return basis<T>::isnan(a);
	}

	template <typename T>
	bool is_zero(T a)
	{
		static T epsilon = (T)1e-5; //std::numeric_limits<T>::epsilon();
		return a == 0 ? true
		     : a > 0 ? a <=  epsilon
		     : a < 0 ? a >= -epsilon
		     : false;
	}

	template <typename T, template <typename> class P>
	bool is_zero(const P<T> &p) { return is_zero((const typename P<T>::b_t &)p); }

	template <typename T>
	bool is_one(T a)
	{
		return eq(a, basis<T>::one());
	}


	template <typename T>
	bool eq(T a, T b)
	{
		return is_zero(b - a);
	}

	template <typename T>
	bool ne(T a, T b)
	{
		return !is_zero(b - a);
	}

	template <typename T>
	bool aeq(T a, T b)
	{
		return eq(a, b) || eq(a, -b);
	}


	template <typename T>
	bool gt(T a, T b)
	{
		return !eq(a, b) && a > b;
	}

	template <typename T>
	bool lt(T a, T b)
	{
		return !eq(a, b) && a < b;
	}

	template <typename T>
	bool gte(T a, T b)
	{
		return eq(a, b) || a > b;
	}

	template <typename T>
	bool lte(T a, T b)
	{
		return eq(a, b) || a < b;
	}
}

#endif // math_precision_h
