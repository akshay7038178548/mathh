#ifndef math_iterator_h
#define math_iterator_h

#include "fwd.h"


namespace math
{
	template <typename T>
	T *simple_deref(const T &i) { return i; }

	template <typename C/*, typename CF = simple_deref*/>
	struct const_index_iterator
	{
		const_index_iterator(typename C::const_iterator &i, const C &c) : i(std::distance(c.begin(), i)), c(c) {}
		const_index_iterator(size_t i, const C &c) : i(i), c(c) {}

		operator size_t () const { return i; }
		const typename C::value_type &operator *() const { return /*CF(*/c[i]/*)*/; }

		const_index_iterator &operator ++()    { i++; return *this; }
		const_index_iterator  operator ++(int) { const_index_iterator r(*this); i++; return r; }

		const_index_iterator operator +(int d) const { const_index_iterator r(*this); r.i += d; return r; }

	protected:
		size_t i;
		const C &c;
	};

	template <typename C/*, template <typename> class CF = simple_deref*/>
	struct index_iterator
	{
		index_iterator(const typename C::iterator &i, C &c) : i(std::distance(c.begin(), i)), c(c) {}
		index_iterator(size_t i, C &c) : i(i), c(c) {}

		operator size_t () const { return i; }
		typename C::value_type &operator *() { return /*CF(*/c[i]/*)*/; }
		const typename C::value_type &operator *() const { return /*CF(*/c[i]/*)*/; }

		index_iterator &operator ++()    { i++; return *this; }
		index_iterator  operator ++(int) { index_iterator r(*this); i++; return r; }

		index_iterator operator +(int d) const { index_iterator r(*this); r.i += d; return r; }

	protected:
		size_t i;
		C &c;
	};
}

#endif // math_iterator_h
