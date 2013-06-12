#ifndef math_compare_h
#define math_compare_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct bi_compare
	{
		static size_t compare(const T &a, const T &b) { return a < b ? 0 : 1; }
	};

	template <typename T>
	struct quad_compare
	{
		static size_t compare(const T &a, const T &b);
	};

	template <typename T>
	struct oct_compare
	{
		static size_t compare(const T &a, const T &b);
	};
}

#endif//math_compare_h
