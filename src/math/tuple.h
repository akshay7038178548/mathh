#ifndef math_tuple_h
#define math_tuple_h

#include "fwd.h"


namespace math
{
	template <typename T>
	struct tuple2_t : public math_tag<tuple2_t<T>> { T d[2]; tuple2_t() {} tuple2_t(T p0, T p1) { d[0] = p0; d[1] = p1; }};
	template <typename T>
	struct tuple3_t : public math_tag<tuple3_t<T>> { T d[3]; tuple3_t() {} tuple3_t(T p0, T p1, T p2) { d[0] = p0; d[1] = p1; d[2] = p2; }};
	template <typename T>
	struct tuple4_t : public math_tag<tuple4_t<T>> { T d[4]; tuple4_t() {} tuple4_t(T p0, T p1, T p2, T p3) { d[0] = p0; d[1] = p1; d[2] = p2; d[3] = p3; }};

	template <typename T>
	inline bool is_null(const tuple2_t<T> &p) { return basis<T>::isnan(p.d[0]) || basis<T>::isnan(p.d[1]); }
	template <typename T>
	inline bool is_null(const tuple3_t<T> &p) { return basis<T>::isnan(p.d[0]) || basis<T>::isnan(p.d[1]) || basis<T>::isnan(p.d[2]); }
	template <typename T>
	inline bool is_null(const tuple4_t<T> &p) { return basis<T>::isnan(p.d[0]) || basis<T>::isnan(p.d[1]) || basis<T>::isnan(p.d[2]) || basis<T>::isnan(p.d[3]); }
}

#endif//math_tuple_h