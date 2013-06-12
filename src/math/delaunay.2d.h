#ifndef math_delaunay_2d_h
#define math_delaunay_2d_h

#include "fwd.h"

#include "figures.h"
#include "convex_hull.2d.h"
#include "mesh.h"


namespace math
{
	template <typename P>
	class delaunay_t : public mesh_t<P>
	{
	public:
		typedef mesh_t<P> mesh_type;
		typedef typename mesh_type::set_type set_type;
	private:
		typedef circle_t<P> circle_type;
		typedef std::vector<circle_type> circles_t;


	private:
		circles_t circles_;


	public:
		delaunay_t(const mesh_type &i)
			: mesh_t<P>(i)
			, circles_(i.size())
		{
			typedef typename mesh_type::face f_t;
			auto i_uf = 0;
			std::for_each(i.begin(), i.end()
				, [this, &i_uf] (f_t f) { this->update_face(i_uf++, f); });
		}

		template <typename I>
		delaunay_t(const I &be, const I &en)
		{
			typename P::t_t y = (*be).y;
			I i = be + 3;

			typename set_type::range_type first_triangle = set_type::insert(be, i);
			std::vector<size_t> tr; tr.push_back(set_face(first_triangle.first, first_triangle.second));
			std::vector<size_t> ntr;
			for (; i != en; i++) {
				P n = (*i); y = n.y;
				for (size_t j = 0; j < tr.size(); j++) {
					size_t itr = tr[j];
					typename mesh_type::face f = this->faces_[itr];
					circle_type cr = circles_[itr];
					triangle_t<P> t = f(*this);

					if (cr.r < (y - cr.c.y))
						continue;

					if (contains(cr, n)) {
						
					} else {
						if ((vector_3d_t<typename P::t_t>(t.b() - n) * vector_3d_t<typename P::t_t>(t.b() - t.a())).z > 0) {
							//this->set_face(f.a, f.b, n);
						}
					}
				}
			}
		}


	public:
		std::vector<size_t> insert(const P &p)
		{
			size_t pi = set_type::insert(p);

			std::vector<size_t> r; r.reserve(4);
			std::vector<size_t> c = find(p);
			std::set<size_t> v;
			std::deque<size_t> d;
			for (std::vector<size_t>::const_iterator ci = c.begin(); ci != c.end(); ++ci) {
				typename mesh_type::face f = this->faces_[*ci];
				v.insert(f.a); v.insert(f.b); v.insert(f.c);
				d.push_back(*ci);
			}

			std::pair<size_t, size_t> k; //k.push_back(*v.begin());
			for (std::set<size_t>::const_iterator vi = ++v.begin(); vi != v.end(); ++vi) {
//				k.push_back(this->items_[*vi]);

				if (d.empty()) {
					circles_.push_back(circumscribe(
						(*(mesh_type::insert(pi, k.first, k.second)))(*this)));
					r.push_back(circles_.size() - 1);
				} else {
					circles_[d.front()] = circumscribe(
						this->faces_[d.front()](pi, k.first, k.second)(*this));
					r.push_back(d.front());
					d.pop_front();
				}
			}

			return r;
		}


	private:
		std::vector<size_t> find(const P &p) {
			std::vector<size_t> r; size_t ri = 0;
			for (typename circles_t::const_iterator ci = circles_.begin(); ci != circles_.end(); ++ci, ++ri) {
				if (contains((*ci), p)) r.push_back(ri);
			}
			return r;
		}

		void update_face(size_t i, typename mesh_type::face f)
		{
			circles_[i] = circumscribe(f(*this));
		}

		size_t set_face(const typename set_type::iterator &b, const typename set_type::iterator &e)
		{
		/*
			typename face_mesh_t<P>::piterator il, ir, ic;
			if (cos(c - a) < cos(c - b)) {
				il = face_mesh_t<P>::insert(a); ir = face_mesh_t<P>::insert(b);
			} else {
				il = face_mesh_t<P>::insert(b); ir = face_mesh_t<P>::insert(a);
			}
			ic = face_mesh_t<P>::insert(c);
		*/
			// should sort cw a,b,c
			typename mesh_type::iterator fi = mesh_type::insert(b, e);
			circles_.push_back(circumscribe((*fi)(*this)));
			return circles_.size() - 1;
		}
/*
		size_t set_face(size_t a, size_t b, const P &c, size_t i = -1)
		{
			size_t ic = std::distance(this->items_.begin(), face_mesh_t<P>::insert(c));

			if (i > this->faces_.size()) {
				typename face_mesh_t<P>::iterator fi = face_mesh_t<P>::insert(a, b, ic);
				circles_.push_back(circumscribe(*fi));
				return circles_.size() - 1;
			} else {
				this->faces_[i](a, b, ic);
				circles_ = circumscribe(this->faces_[i](&this));
				return i;
			}
		}
*/
	};
}

#endif // math_delaunay_2d_h
