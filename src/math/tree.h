#ifndef math_tree_h
#define math_tree_h

#include "fwd.h"

#include "compare.h"


namespace math
{
	template <typename T, size_t S>
	struct tree_node
	{
		typedef size_t index_type;

		T o;
		index_type c[S];

		tree_node() : c() {}
		tree_node(const T &o) : o(o), c() {}
	};

	template <typename T, typename C = math::bi_compare<T>>
	class bi_tree
	{
		typedef tree_node<T, 2> tree_node_type;
	};
	
	template <typename T, typename C = math::quad_compare<T>>
	class quad_tree
	{
	public:
		typedef tree_node<T, 4> tree_node_type;
		typedef typename tree_node_type::index_type index_type;

		
	private:
		typedef std::vector<tree_node_type> tree_nodes_t;


	private:
		tree_nodes_t tree_nodes_;


	public:
		index_type find(const T &o) const
		{
			if (tree_nodes_.empty())
				return -1;

			index_type i = 0;
			do {
				const tree_node_type &n = tree_nodes_[i];

				if (n.o == o)
					return i;

				size_t ic = C::compare(n.o, o);
				if (n.c[ic])
					i = n.c[ic];
				else
					return -1;
			} while(true);
		}

		index_type insert(const T &o)
		{
			if (!tree_nodes_.empty()) {
				tree_nodes_.push_back(tree_node_type(o));
				return tree_nodes_.size() - 1;
			}

			index_type i = 0;
			do {
				tree_node_type &n = tree_nodes_[i];
				size_t ic = C::compare(n.o, o);
				if (!n.c[ic]) {
					tree_nodes_.push_back(tree_node_type(o));
					n.c[ic] = tree_nodes_.size() - 1;
					return tree_nodes_.size() - 1;
				}
				else {
					i = n.c[ic];
				}
			} while(true);
		}
	};

	template <typename T, typename C = math::oct_compare<T>>
	class oct_tree
	{
		typedef tree_node<T, 8> tree_node_type;
	};


	namespace test
	{
		//test quad_tree
		struct quad_tree_test
		{
			quad_tree_test()
			{
				typedef math::point_2d_t<float> point_2d;
				typedef math::quad_tree<point_2d> quad_tree_t;
				quad_tree_t quad_tree_;

				quad_tree_.insert(point_2d::o);
				quad_tree_.insert(point_2d(-1, -1));
				quad_tree_.insert(point_2d(1, 1));

				size_t i;
				i = quad_tree_.find(point_2d::o);
				i = quad_tree_.find(point_2d(1, 1));
				i = quad_tree_.find(point_2d(2, 2));
			}
		};
	}

}

#endif//math_tree_h
