#ifndef math_voronoi_2d_h
#define math_voronoi_2d_h

#include "fwd.h"


namespace math
{
	template <typename P>
	class voronoi_t
	{
	private:
		typedef std::vector<std::pair<P, size_t/*dcel_i*/>> faces_t;
		typedef std::vector<std::pair<P, size_t/*dcel_i*/>> vertices_t;
		struct dcel { size_t vb, ve, fr, fl, en, ep; };
		typedef std::vector<dcel> dcel_t;



	private:
		faces_t faces_;
		vertices_t vertices_;
		dcel_t dcel_;



	public:
		template <typename I>
		voronoi_t(const I &b, const I &e)
		{
			for (I i = b; i != e; ++i) {
				P p = (*i);
				size_t fi = faces_.size(); faces_.push_back(std::make_pair(p, -1));

			}
		}

		size_t find(const P &p) const
		{
			for (size_t i = faces_.size(); i > 0; --i) {
				std::vector<size_t> ri = region(i);
				std::vector<P> rp(ri.size());
				std::transform(ri.begin(), ri.end(), rp.begin(), [this](size_t vi){ return this->vertices_[vi]; });

				if (contains(rp.begin(), rp.end(), p)) {
					
				}
			}

			return -1;
		}

	private:
		std::vector<size_t> region(size_t fi) const
		{
			std::vector<size_t> r;
			size_t i = faces_[fi].second;
			if (i == -1) return r;

			do {
				r.push_back(dcel_[i].ve);
				i = dcel_[i].en;
			} while(i != faces_[fi].second);

			return r;
		}
	};
}

#endif // math_voronoi_2d_h
