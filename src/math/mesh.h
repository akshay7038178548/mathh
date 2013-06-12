#ifndef math_mesh_h
#define math_mesh_h

#include "fwd.h"

//#include "graph.h"
#include "set.h"


namespace math
{
	template <typename T>
	class mesh_t : protected set_t<T>
	{
	public:
		typedef typename set_t<T>::index_type index_type;


	protected:
		struct face_t : public std::tuple<index_type, index_type, index_type>
		{
			//using std::tuple<index_type, index_type, index_type>;
			face_t(index_type ia, index_type ib, index_type ic)
				: std::tuple<index_type, index_type, index_type>(ia,ib,ic) {}
		};
		typedef std::vector<face_t> faces_t;


	protected:
		faces_t faces_;


	public:
		mesh_t() {}

		//template <typename I> mesh_t(const I b, const I e) : graph(b, e) {}
		//mesh_t(graph &&g) /* pointless long calculations */ {}

		mesh_t(const array<T> &d, const array<index_type> &i)
			: set_t<T>(d)
			, faces_(i.begin(), i.end())
		{}

		//template <typename T> T convex();

	public:
		using set_t<T>::item;
		using set_t<T>::item_array;
		const array<index_type> face_index() const {
			return array<index_type>(reinterpret_cast<index_type *>(&faces_.front()), faces_.size() * 3); }



	public:
		using set_t<T>::insert;
		//using graph<T>::link;
		//using graph<T>::unlink;
		//size_t group(std::initializer_list n)
		//{}
		index_type group(index_type ia, index_type ib, index_type ic)
		{
			faces_.push_back(face_t(ia,ib,ic));
			return faces_.size() - 1;
		}
		bool ungroup(index_type ig)
		{
			//spare_faces_.insert(ig);
			return false;
		}


#ifdef SERIALIZATION
	public:
		mesh_t(core::istream &s)
			: set_t<T>(s)
			, faces_(deserialize(s, faces_))
		{}
#endif//SERIALIZATION
	};

	namespace test
	{
		//test mesh_t
		struct mesh_test
		{
			mesh_test()
			{
				typedef math::mesh_t<int> mesh_t;
				mesh_t mesh_;
			}
		};
	}
}

#ifdef SERIALIZATION
//namespace math
//{
	template <typename T>
	inline
	void serialize(const math::mesh_t<T> &o, core::ostream &s)
	{
		s << o.item_array() << o.face_index();
	}
//}
#endif//SERIALIZATION

#endif//math_mesh_h
