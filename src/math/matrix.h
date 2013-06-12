#ifndef math_matrix_h
#define math_matrix_h

#include "fwd.h"

//#include "primitives.h"
//#include "quaternion.h"


namespace math
{
	template <typename T, size_t S>
	matrix<T, S> &identity(matrix<T, S> &m);

	template <typename T, size_t S>
	struct matrix
	{
		enum { size = S };

		T m[S*S];

		vector_3d_t<T> &ox() { return *reinterpret_cast<vector_3d_t<T> *>(&m[0]); }
		vector_3d_t<T> &oy() { return *reinterpret_cast<vector_3d_t<T> *>(&m[4]); }
		vector_3d_t<T> &oz() { return *reinterpret_cast<vector_3d_t<T> *>(&m[8]); }
		vector_3d_t<T> &tr() { return *reinterpret_cast<vector_3d_t<T> *>(&m[12]); }


		matrix()
		{
			identity(*this);
		}

		matrix(vector_3d_t<T> t, vector_3d_t<T> x, vector_3d_t<T> y, vector_3d_t<T> z)
		{
			ox() = x; oy() = y; oz() = z; tr() = t;
			m[3] = m[7] = m[11] = 0; m[15] = 1;
		}

		matrix(T d[S*S])
		{
			std::memcpy(m, d, S*S * sizeof(T));
		}

		matrix(const matrix &c)
		{
			std::memcpy(m, c.m, S*S * sizeof(T));
		}

		matrix &operator =(const matrix &r)
		{
			std::memcpy(m, r.m, S*S * sizeof(T));
			return *this;
		}

		template <typename U>
		explicit matrix(const matrix<U, S> &c)
		{
			for (size_t i = 0; i < S*S; i++) {
				m[i] = math_cast<T>(c.m[i]);
			}
		}


		const T &operator ()(int r, int c) const { assert(r < S && c < S); return m[r + c*S]; }
		T &operator ()(int r, int c)             { assert(r < S && c < S); return m[r + c*S]; }


		matrix<T, S-1> redux() const
		{
			matrix<T, S-1> r;
			for (size_t c = 0; c < S-1; c++)
				std::memcpy(r.m[c * (S-1)], m[c * S], S-1);
			return r;
		}
	};

	template <typename T, size_t S, size_t eR, size_t eC>
	struct matrix_redux
	{
		enum { size = S };

		T &operator ()(int r, int c) { return m(iR(r), iC(c)); }

	private:
		size_t iR(size_t r) { return r < eR ? r : r + 1; }
		size_t iC(size_t c) { return c < eC ? c : c + 1; }
		matrix<T, S> &m;
	};

	template <typename T, size_t S> 
	inline
		matrix<T, S> 
		operator *(const matrix<T, S> &a, const matrix<T, S> &b)
	{
		matrix<T, S> m;

		for (size_t r = 0; r < S; r++) {
			for (size_t c = 0; c < S; c++) {
				m(r,c) = basis<T>::zero();
				for (size_t n = 0; n < S; n++) {
					m(r,c) += a(r,n)*b(n,c);
				}
			}
		}

		return m;
	}

	template <typename T, size_t S> 
	inline
		bool
		operator ==(const matrix<T, S> &a, const matrix<T, S> &b)
	{
		matrix<T, S> m;

		for (size_t i = 0; i < S*S; i++) {
			if (ne(a.m[i], b.m[i])) return false;
		}

		return true;
	}
}

#endif // math_matrix_h
