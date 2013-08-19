#ifndef math_graph_h
#define math_graph_h

#include "fwd.h"

#include "set.h"


namespace math
{
	template <typename T>
	class graph_t : protected set_t<T>
	{
	private:
		typedef std::map<size_t, std::set<size_t>> links_t;
		links_t alinks_;
		links_t blinks_;


	public:
		using set_t<T>::size;

		using set_t<T>::insert;
		//using set_t<T>::remove;

		std::pair<size_t, bool> link(size_t ia, size_t ib)
		{
			// if (links_.count(ia).count(ib))
			alinks_[ia].insert(ib);
			blinks_[ib].insert(ia);

			return {};
		}
	};
}

#endif//math_graph_h
