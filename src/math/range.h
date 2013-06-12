#ifndef math_range_h
#define math_range_h


namespace math
{
	template <typename T>
	struct range_t
	{
		T a; T b;

		range_t() : a(), b() {}
		range_t(const T &a, const T &b) : a(a), b(b) {}
	};
}

#endif//math_range_h
