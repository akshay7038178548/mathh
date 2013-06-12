#ifndef math_array_h
#define math_array_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct array : public std::pair<T *, size_t>
	{
		array(T *d, size_t s) : std::pair<T *, size_t>(d, s) {}

		const T *begin() const { return first; }
		const T *end()   const { return first + second; }
		T *begin()             { return first; }
		T *end()               { return first + second; }
	};
}

#ifdef SERIALIZATION
//namespace math
//{
	template <typename T>
	inline
	void serialize(const math::array<T> &o, core::ostream &s)
	{
		serialize(o.first, o.second);
	}
//}
#endif//SERIALIZATION

#endif//math_array_h
