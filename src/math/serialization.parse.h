#ifndef math_serialization_parse_h
#define math_serialization_parse_h

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

//namespace math
//{
	template <typename T>
	inline
	std::string to_string(math::vector_2d_t<T> &v)
	{
		return (boost::format("%1%:%2%") % v.x % v.y).str();
	}

	template <typename T>
	inline
	math::vector_2d_t<T> parse(const std::string &s, math::vector_2d_t<T> &)
	{
		boost::char_separator<char> sep(":,");
		boost::tokenizer<boost::char_separator<char>> tok(s, sep);
		
		math::vector_2d_t<T> v(0, 0); int i = 0;
		
		for (auto ti = tok.begin(); ti != tok.end(); ++ti, ++i) {
			switch (i) {
			case 0: v.x = boost::lexical_cast<T>(*ti); break;
			case 1: v.y = boost::lexical_cast<T>(*ti); break;
			}
		}

		return v;
	}
//}

#endif//math_serialization_parse_h
