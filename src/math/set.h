#ifndef math_set_h
#define math_set_h

#include "fwd.h"

#include "array.h"


namespace math
{
	template <typename T>
	class set_t
	{
	private:
		typedef std::vector<T> items_t;
	public:
		typedef typename items_t::iterator iterator;
		typedef typename items_t::const_iterator const_iterator;
		typedef T value_type;
		typedef size_t index_type;
		typedef std::pair<index_type, index_type> range_type;


	protected:
		items_t items_;



	public:
		set_t() {}
		template <typename I>
		set_t(const I &b, const I &e) : items_(b, e) {}
		
		set_t(const array<T> &d) : items_(d.begin(), d.end()) {}


	public:
		size_t size() const          { return items_.size(); }
		iterator begin()             { return items_.begin(); }
		iterator end()               { return items_.end(); }
		const_iterator begin() const { return items_.begin(); }
		const_iterator end() const   { return items_.end(); }

		const T &item(index_type i) const { assert(i < items_.size()); return items_[i]; }

		const array<const T> item_array() const {
			return array<const T>(&items_.front(), items_.size()); }


	public:
		bool repack()
		{
			/*
			if (!spare_items_.empty()) {
				return true;
			}
			*/
			return false;
		}


		index_type find(const T &i) const
		{
			iterator ii = std::find(items_.begin(), items_.end(), i);
			if (ii != items_.end())
				return ii - items_.begin();
			return -1;
		}

		index_type insert(const T &i)
		{
			//if (spare_items_.empty()) {
			items_.push_back(i);
			return items_.size() - 1;
			//}
			/* else {
			index_type ii = *spare_items_.begin();
			spare_items_.erase(ii);
			items_[ii] = i;
			return i;
			*/
		}

		template <typename I>
		range_type insert(const I &b, const I &e)
		{
			index_type first = items_.size();

			for (I i = b; i != e; ++i) {
				items_.push_back(*i);
			}

			return range_type(first, items_.size());
		}

		bool remove(index_type i)
		{
			/*
			if (!spare_items_.count(i)) {
				spare_items_.insert(i);
				return true;
			}
			*/
			return false;
		}


#ifdef SERIALIZATION
	public:
		set_t(core::istream &s)
			: items_(deserialize(s, items_))
		{}
#endif//SERIALIZATION
	};

	namespace test
	{
		//test mesh
		struct set_test
		{
			set_test()
			{
				typedef math::set_t<int> set_t;
				set_t set_;
			}
		};
	}
}

#ifdef SERIALIZATION
//namespace math
//{
	template <typename T>
	inline
	void serialize(const math::set_t<T> &o, core::ostream &s)
	{
		s << o.items_array();
	}
//}
#endif//SERIALIZATION

#endif//math_set_h
