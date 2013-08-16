#ifndef math_serialization_parse_h
#define math_serialization_parse_h

//namespace math
//{
	template <typename T>
	inline
	math::vector_2d_t<T> parse(const std::string &s, math::vector_2d_t<T> &)
	{
		math::vector_2d_t<T> v(640, 480);		
		return v;
	}
//}

#endif//math_serialization_parse_h
