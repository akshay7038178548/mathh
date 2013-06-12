#ifndef math_basis_h
#define math_basis_h

#include <limits>
#include <boost/math/special_functions/fpclassify.hpp>


/*
	t_t - element type
	f_t - best float type for t_t
	b_t - p_t or v_t
	p_t - point of t_t
	v_t - vector_3d of t_t
	d_t - part of volume
	r_t - rotation
	m_t - matrix transformation

*/

#define DECLARE_BASIS_2D(t) \
	typedef t t_t; \
	typedef typename ::math::basis<t_t>::f_t f_t; \
	typedef point_2d_t<t_t> p_t; \
	typedef vector_2d_t<t_t> v_t; \
	typedef aabb_t<p_t> d_t


#define DECLARE_BASIS_3D(t) \
	typedef t t_t; \
	typedef typename ::math::basis<t_t>::f_t f_t; \
	typedef point_3d_t<t_t> p_t; \
	typedef vector_3d_t<t_t> v_t; \
	typedef aabb_3d<t_t> d_t


#define INHERIT_BASIS(_bp) \
	typedef typename _bp::t_t t_t; \
	typedef typename _bp::f_t f_t; \
	typedef _bp b_t; \
	typedef typename _bp::p_t p_t; \
	typedef typename _bp::v_t v_t; \
	typedef typename _bp::d_t d_t




namespace math
{
	template <typename T>
	struct basis {};

	template <>
	struct basis<unsigned char>
	{
		typedef float f_t;

		static f_t f(unsigned char v) { return f_t(v); }

		static bool exact(unsigned char v) { return !(v % 2); }
		static bool squared(unsigned char v) { return !!(v % 2); }

		//static unsigned char nan() { return std::numeric_limits<unsigned char>::max(); }

		static unsigned char zero() { return 0; }
		static unsigned char one() { return 1; }

		static unsigned char min() { return std::numeric_limits<unsigned char>::min(); }
		static unsigned char max() { return std::numeric_limits<unsigned char>::max(); }
	};

	template <>
	struct basis<int>
	{
		typedef float f_t;

		static f_t f(int v) { return f_t(v); }

		static bool exact(int v) { return !(v % 2); }
		static bool squared(int v) { return !!(v % 2); }

		static int nan() { return std::numeric_limits<int>::min(); }
		static bool isnan(int v) { return v == nan(); }

		static int zero() { return 0; }
		static int one() { return 1; }

		static int min() { return std::numeric_limits<int>::min() + 1; }
		static int max() { return std::numeric_limits<int>::max(); }
	};

	template <>
	struct basis<unsigned int>
	{
		typedef float f_t;

		static f_t f(unsigned int v) { return f_t(v); }

		static bool exact(unsigned int v) { return !(v % 2); }
		static bool squared(unsigned int v) { return !!(v % 2); }

		static unsigned int nan() { return std::numeric_limits<unsigned int>::max(); }
		static bool isnan(unsigned int v) { return v == nan(); }

		static unsigned int zero() { return 0; }
		static unsigned int one() { return 1; }

		static unsigned int min() { return std::numeric_limits<unsigned int>::min(); }
		static unsigned int max() { return std::numeric_limits<unsigned int>::max() - 1; }
	};

	template <>
	struct basis<float>
	{
		typedef float f_t;

		static f_t f(float v) { return v; }

		static bool exact(float) { return true; }
		static bool squared(float) { return false; }

		static float nan() { return std::numeric_limits<float>::quiet_NaN(); }
		static bool isnan(float v) { return boost::math::isnan(v); }

		static float zero() { return 0.f; }
		static float one() { return 1.f; }

		static float min() { return zero(); }
		static float max() { return one(); }
	};

	template <>
	struct basis<double>
	{
		typedef double f_t;

		static f_t f(double v) { return v; }

		static bool exact(double) { return true; }
		static bool squared(double) { return false; }

		static double nan() { return std::numeric_limits<double>::quiet_NaN(); }
		static bool isnan(double v) { return boost::math::isnan(v); }

		static double zero() { return 0.; }
		static double one() { return 1.; }

		static double min() { return zero(); }
		static double max() { return one(); }
	};

	template <typename U, typename T>
	T scale(U u)
	{
		return (T)(basis<U>::f(u) / basis<U>::max() * basis<T>::max());
	}

	template <typename FT, size_t D>
	struct dimensions
	{
		typedef int r_t;
		typedef int m_t;
	};
/*
	template <typename FT>
	struct dimensions<FT, 2>
	{
		typedef ::math::complex<FT> r_t;
		typedef ::math::matrix<FT, 3> m_t;
	};

	template <typename FT>
	struct dimensions<FT, 3>
	{
		typedef ::math::quaternion<FT> r_t;
		typedef ::math::matrix<FT, 4> m_t;
	};
*/
}

/*
#define MATH_GUESS_BASIS(p) \
	typedef typename p::t_t t_t; \
	typedef typename p::f_t f_t; \
	typedef typename p::b_t b_t; \
	typedef p p_t; \
	typedef typename p::v_t v_t; \
	typedef typename p::d_t d_t; \
	typedef typename p::r_t r_t; \
	typedef typename p::m_t m_t


#define MATH_INHERIT_BASIS(_bp) \
	typedef typename _bp::t_t t_t; \
	typedef typename _bp::f_t f_t; \
	typedef typename _bp::b_t b_t; \
	typedef typename _bp::p_t p_t; \
	typedef typename _bp::v_t v_t; \
	typedef typename _bp::d_t d_t; \
	typedef typename _bp::r_t r_t; \
	typedef typename _bp::m_t m_t
*/

#endif // math_basis_h
