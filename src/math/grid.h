#ifndef math_grid_h
#define math_grid_h

#include "fwd.h"

#include "set.h"


namespace math
{
	template <typename P, typename T>
	class grid_defaults
	{
		typedef P p_t;
		typedef typename P::v_t v_t;

		static v_t default_top() { return v_t(50, 50, 50); }
	};

	template <typename P, typename T, typename V>
	class grid_node
	{
		P center;
		grid_node *up;
		grid_node *down[2*2*2];
		V value;

		grid_node(const P &c, const V &v)
			: up(nullptr)
			, down({})
			, center(c)
			, value(v)
		{
		}

		size_t index(const P &p) const
		{
			int i = 0;
			if (p.x > c.x) i &= 0x01;
			if (p.y > p.y) i &= 0x02;
			if (p.z > p.z) i &= 0x04;
			return i;
		}
	};

	template <typename P, typename T, typename V = std::pair<P, T>>
	class grid
	{
		typedef P p_t;
		typedef typename P::v_t v_t;

		typedef V value_type;
		typedef grid_node<P, T, V> node_type;
		typedef grid_node *iterator;

		aabb_t<P> bound;
		node_type *top;

		iterator insert(const value_type &v)
		{
			if (!top)
				return create_top(v);
			if (!contains(bound, v.first))
				return expand_top(v);
		}

		iterator create_top(const value_type &v)
		{
			bound = aabb_t<P>(v.first, v_t(50, 50, 50)) - v_t(25, 25, 25);
			top = new node_type(bound.o(), v);
			return top;
		}

		iterator expand_top(const value_type &v)
		{
			int i = reinterpret_cast<node_type *>(&v.first)->index(top->center);
			bound = aabb_t<P>(bound.p(~i)
				, v_t(!(i & 0x01) ? bound.w() : -bound.w(), !(i & 0x02) ? bound.h() : -bound.h(), !(i & 0x03) ? bound.d() : -bound.d()));
			top->up = new node_type(bound.o(), )
			return top;
		}
	};

	template <typename P>
	class voxel_space
	{
	public:
		typedef void *iterator;
	};

	template <typename T, typename V>
	class grid<math::point_2d_t<float>, T, V>
	{
	public:
		typedef math::point_2d_t<float> p_t;

		typedef math::range_t<std::size_t> index_type;
		typedef V cell_t;


	private:
		typedef math::voxel_space<p_t> cells_t;
		cells_t cells_;
		std::map<cells_t::iterator, V> data_;


	public:
		grid(math::aabb_t<p_t> b)
			: boundary_(b)
		{

		}

		grid &subdivide(index_type c)
		{


			return *this;
		}

		const cell_t &operator [](index_type i) const { return data_[cells_[i]]; }

		cell_t &operator [](index_type i)
		{
			return cells_[i];
		}

	private:
		math::aabb_t<p_t> boundary_;
	};

	namespace test
	{
		class room;

		//test grid
		struct grid_test
		{
			grid_test() {
				typedef math::point_2d_t<float> p_t;
				typedef math::grid<math::point_2d_t<float>, room> room_t;

				//room_t room_(math::aabb_2d<10.f>())); - so much fun :)))))
				//if can call template constructor of not template class
				room_t room_(math::aabb_t<p_t>(p_t({10.f,10.f})));
				room_.subdivide({4, 4});


			}
		};

		class room
		{

		};
	}

	template <>
	class grid_t<math::point_2d_t<float>>
		: public set_t<math::point_2d_t<float>>
	{
	public:
		index_type find(const value_type &i) const
		{
			const_iterator ii = std::find(items_.begin(), items_.end(), i);
			if (ii != items_.end())
				return ii - items_.begin();
			return -1;
		}

		index_type insert(const value_type &i)
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
	};
}

#endif//math_grid_h
