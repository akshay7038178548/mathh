#ifndef math_serialization_h
#define math_serialization_h

//namespace math
//{
	template <typename T>
	inline
	void serialize(const math::color_t<T> &c, core::ostream &s)
	{
		s << c.r << c.g << c.b;
	}

	template <typename T>
	inline
	void serialize(const math::vector_2d_t<T> &v, core::ostream &s)
	{
		s << v.x << v.y;
	}

	template <typename T>
	inline
	void serialize(const math::point_2d_t<T> &p, core::ostream &s)
	{
		s << p.x << p.y;
	}

	template <typename T>
	inline
	void serialize(const math::vector_3d_t<T> &v, core::ostream &s)
	{
		s << v.x << v.y << v.z;
	}

	template <typename T>
	inline
	void serialize(const math::point_3d_t<T> &p, core::ostream &s)
	{
		s << p.x << p.y << p.z;
	}

	template <typename T>
	inline
	void serialize(const math::complex<T> &c, core::ostream &s)
	{
		s << c.a() << c.b();
	}

	template <typename T>
	inline
	void serialize(const math::quaternion<T> &q, core::ostream &s)
	{
		s << q.w() << q.x() << q.y() << q.z();
	}


	template <typename T>
	inline
	math::color_t<T> deserialize(core::istream &s, math::color_t<T> &)
	{
		math::color_t<T> c;
		s >> c.r >> c.g >> c.b;
		return c;
	}

	template <typename T>
	inline
	math::point_2d_t<T> deserialize(core::istream &s, math::point_2d_t<T> &)
	{
		math::point_2d_t<T> p;
		s >> p.x >> p.y;
		return p;
	}

	template <typename T>
	inline
	math::vector_2d_t<T> deserialize(core::istream &s, math::vector_2d_t<T> &)
	{
		math::vector_2d_t<T> v;
		s >> v.x >> v.y;
		return v;
	}

	template <typename T>
	inline
	math::point_3d_t<T> deserialize(core::istream &s, math::point_3d_t<T> &)
	{
		math::point_3d_t<T> p;
		s >> p.x >> p.y >> p.z;
		return p;
	}

	template <typename T>
	inline
	math::vector_3d_t<T> deserialize(core::istream &s, math::vector_3d_t<T> &)
	{
		math::vector_3d_t<T> v;
		s >> v.x >> v.y >> v.z;
		return v;
	}

	template <typename T>
	inline
	math::complex<T> deserialize(core::istream &s, math::complex<T> &)
	{
		T a, b;
		s >> a >> b;
		return math::complex<T>(a, b);
	}

	template <typename T>
	inline
	math::quaternion<T> deserialize(core::istream &s, math::quaternion<T> &)
	{
		T w, x, y, z;
		s >> w >> x >> y >> z;
		return math::quaternion<T>(w, x, y, z);
	}
//}

#endif // math_serialization_h
