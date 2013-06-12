#ifndef math_color_h
#define math_color_h

#include "fwd.h"


namespace math
{
	template <typename T, typename U>
	color_hsl_t<U> &rgb_to_hsl(const color_t<T> &rgb, color_hsl_t<U> &hsl);

	template <typename T, typename U>
	color_t<U> &hsl_to_rgb(const color_hsl_t<T> &hsl, color_t<U> &rgb);

	template <typename T, typename U>
	color_hsv_t<U> &rgb_to_hsv(const color_t<T> &rgb, color_hsv_t<U> &hsv);

	template <typename T, typename U>
	color_t<U> &hsv_to_rgb(const color_hsv_t<T> &hsv, color_t<U> &rgb);



	template <typename T>
	struct color_t
	{
		T r;
		T g;
		T b;


		static color_t<T> black;
		static color_t<T> white;

		static color_t<T> red;
		static color_t<T> green;
		static color_t<T> blue;

		static color_t<T> yellow;
		static color_t<T> olive;
		static color_t<T> magenta;
		static color_t<T> purple;
		static color_t<T> cyan;
		static color_t<T> teal;

		static color_t<T> light_blue;
		static color_t<T> dark_blue;


		color_t()
			: r(0), g(0), b(0)
		{
		}

		color_t(T r, T g, T b)
			: r(r), g(g), b(b)
		{
		}

		explicit
		color_t(const T *d)
			: r(d[0])
			, g(d[1])
			, b(d[2])
		{
		}

		color_t(std::initializer_list<T> d)
			: color_t(d.begin())
		{
		}

		color_t(const color_t &c)
			: r(c.r), g(c.g), b(c.b)
		{
		}

		template <typename U>
		explicit color_t(const color_t<U> &c)
			: r(scale<U, T>(c.r))
			, g(scale<U, T>(c.g))
			, b(scale<U, T>(c.b))
		{
		}

		template <typename U>
		explicit color_t(const color_hsl_t<U> &hsl)
		{
			hsl_to_rgb(hsl, *this);
		}

		template <typename U>
		explicit color_t(const color_hsv_t<U> &hsv)
		{
			hsv_to_rgb(hsv, *this);
		}

		color_t &reset(T r, T g, T b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		} 
	};



	template <typename T, typename U>
	static bool operator ==(const color_t<T> &l, const color_t<U> &r);

	template <typename T, typename U>
	static bool operator !=(const color_t<T> &l, const color_t<U> &r);


	template<typename T, typename U>
	static bool operator <(const color_t<T> &l, const color_t<U> &r);



	template <typename T>
	struct color_hsl_t
	{
		T h;
		T s;
		T l;


		color_hsl_t()
			: h(0), s(0), l(0)
		{
		}

		color_hsl_t(T h, T s, T l)
			: h(h), s(s), l(l)
		{
		}

		color_hsl_t(const color_hsl_t &c)
			: h(c.h), s(c.s), l(c.l)
		{
		}

		template <typename U>
		explicit color_hsl_t(const color_t<U> &rgb)
		{
			rgb_to_hsl(rgb, *this);
		}


		color_hsl_t norm() const
		{
			color_hsl_t n(*this);
			n.normalize();
			return n;
		}

		color_hsl_t &normalize()
		{
			while (h >= 360.f) h -= 360.f;
			while (h < 0) h += 360.f;
			if (s > 1.f) s = 1.f;
			else if (s < 0) s = 0;
			if (l > 1.f) l = 1.f;
			else if (l < 0) l = 0;
		}
	};


	template <typename T, typename U>
	static bool operator ==(const color_hsl_t<T> &l, const color_hsl_t<U> &r);

	template <typename T, typename U>
	static bool operator !=(const color_hsl_t<T> &l, const color_hsl_t<U> &r);


	template<typename T, typename U>
	static bool operator <(const color_hsl_t<T> &l, const color_hsl_t<U> &r);



	template <typename T>
	struct color_hsv_t
	{
		T h;
		T s;
		T v;


		color_hsv_t()
			: h(0), s(0), v(0)
		{
		}

		color_hsv_t(T h, T s, T v)
			: h(h), s(s), v(v)
		{
		}

		color_hsv_t(const color_hsv_t &c)
			: h(c.h), s(c.s), v(c.v)
		{
		}

		template <typename U>
		explicit color_hsv_t(const color_t<U> &rgb)
		{
			rgb_to_hsv(rgb, *this);
		}


		color_hsv_t norm() const
		{
			color_hsv_t n(*this);
			n.normalize();
			return n;
		}

		color_hsv_t &normalize()
		{
			while (h >= 360.f) h -= 360.f;
			while (h < 0) h += 360.f;
			if (s > 1.f) s = 1.f;
			else if (s < 0) s = 0;
			if (v > 1.f) v = 1.f;
			else if (v < 0) v = 0;
		}
	};


	template <typename T, typename U>
	static bool operator ==(const color_hsv_t<T> &l, const color_hsv_t<U> &r);

	template <typename T, typename U>
	static bool operator !=(const color_hsv_t<T> &l, const color_hsv_t<U> &r);


	template<typename T, typename U>
	static bool operator <(const color_hsv_t<T> &l, const color_hsv_t<U> &r);



	// _conversion

	template <typename T, typename U>
	color_hsl_t<U> &rgb_to_hsl(const color_t<T> &rgb, color_hsl_t<U> &hsl)
	{
		T r = rgb.r, g = rgb.g, b = rgb.b;

		U uMax = max( r, g, b );
		U uMin = min( r, g, b );

		hsl.l = (uMax + uMin) / 2.f;

		if (uMax != 0) {
			hsl.s = (uMax - uMin) / uMax;
		}
		else {
			hsl.s = 0;
		}

		if (hsl.s == 0) {
			hsl.s = -1.f;
		}
		else {
			U d = uMax - uMin;

			if (uMax == r) {
				hsl.h = (g - b) / d;
			}
			else if (uMax == g) {
				hsl.h = 2.f + (b - r) / d;
			}
			else {
				hsl.h = 4.f + (r - g) / d;
			}

			hsl.h *= 60.f;

			if (hsl.h < 0) hsl.h += 360.f;
			else if (hsl.h >= 360.f) hsl.h -= 360.f;
		}

		return hsl;
	}

	template <typename T, typename U>
	color_t<U> &hsl_to_rgb(const color_hsl_t<T> &hsl, color_t<U> &rgb)
	{
		if (hsl.s == 0.f) {
			rgb.r = rgb.g = rgb.b = hsl.l;
		}
		else {
			T hue = hsl.h / 60.f;
			int i = hue;
			T   f = hue - i;

			T p = ( hsl.z <= 0.5F )
				? hsl.z * (1.0F - hsl.y)
				: hsl.z * (1.0F + hsl.y) - hsl.y;

			T s1 = hsl.y * (1.0F - 2.0F * f);
			T s2 = hsl.y * (2.0F * f - 1.0F);
			T t = ( hsl.z <= 0.5F )
				? hsl.z * (1.0F - s1)
				: hsl.z * (1.0F - s2);
			T q = ( hsl.z <= 0.5F )
				? hsl.z * (1.0F - s2) - s1
				: hsl.z * (1.0F - s1) - s2;

			T u = ( hsl.z <= 0.5F )
				? hsl.z * (1.0F + hsl.y)
				: hsl.z * (1.0F - hsl.y) + hsl.y;

			switch (i) {
			case 0: rgb.reset(u, t, p);
				break;
			case 1: rgb.reset(q, u, p);
				break;
			case 2: rgb.reset(p, u, t);
				break;
			case 3: rgb.reset(p, q, u);
				break;
			case 4: rgb.reset(t, p, u);
				break;
			case 5: rgb.reset(u, p, q);
				break;
			}
		}

		return rgb;
	}

	template <typename T, typename U>
	color_hsv_t<U> &rgb_to_hsv(const color_t<T> &rgb, color_hsv_t<U> &hsv)
	{
		T r = rgb.r, g = rgb.g, b = rgb.b;

		U uMax = max( r, g, b );
		U uMin = min( r, g, b );

		hsv.v = uMax;

		if (uMax != 0) {
			hsv.s = (uMax - uMin) / uMax;
		}
		else {
			hsv.s = 0;
		}

		if (hsv.s == 0) {
			hsv.s = -1.f;
		}
		else {
			U d = uMax - uMin;

			if (uMax == r) {
				hsv.h = (g - b) / d;
			}
			else if (uMax == g) {
				hsv.h = 2.f + (b - r) / d;
			}
			else {
				hsv.h = 4.f + (r - g) / d;
			}

			hsv.h *= 60.f;

			if (hsv.h < 0) hsv.h += 360.f;
			else if (hsv.h >= 360.f) hsv.h -= 360.f;
		}

		return hsv;
	}

	template <typename T, typename U>
	color_t<U> &hsv_to_rgb(const color_hsv_t<T> &hsv, color_t<U> &rgb)
	{
		if (hsv.s == 0.f) {
			rgb.r = rgb.g = rgb.b = hsv.v;
		}
		else {
			T hue = hsv.h / 60.f;
			int i = hue;
			T   f = hue - i;

			T p = hsv.v * (1.0F - hsv.s);
			T q = hsv.v * (1.0F - hsv.s * f);
			T t = hsv.v * (1.0F - hsv.s * (1.0F - f));

			switch (i) {
			case 0: rgb.rest(hsv.v, t, p);
				break;
			case 1: rgb.rest(q, hsv.z, p);
				break;
			case 2: rgb.rest(p, hsv.z, t);
				break;
			case 3: rgb.rest(p, q, hsv.z);
				break;
			case 4: rgb.rest(t, p, hsv.z);
				break;
			case 5: rgb.rest(hsv.z, p, q);
				break;
			}
		}

		return rgb;
	}



	// _operator

	template <typename T, typename U>
	static bool operator ==(const color_t<T> &l, const color_t<U> &r)
	{
		return l.r == r.r && l.g == r.g && l.b == r.b;
	}

	template <typename T, typename U>
	static bool operator !=(const color_t<T> &l, const color_t<U> &r)
	{
		return !(l == r);
	}
	
	template<typename T, typename U>
	static bool operator <(const color_t<T> &l, const color_t<U> &r)
	{
		return lt(l.b, r.b)
		    || (eq(l.b, r.b) && (lt(l.g, r.g)
		                      || (eq(l.g, r.g) && lt(l.r, r.r))));
	}


	template <typename T, typename U>
	static bool operator ==(const color_hsl_t<T> &l, const color_hsl_t<U> &r)
	{
		return l.h == r.h && l.s == r.s && l.l == r.l;
	}

	template <typename T, typename U>
	static bool operator !=(const color_hsl_t<T> &l, const color_hsl_t<U> &r)
	{
		return !(l == r);
	}


	template <typename T, typename U>
	static bool operator ==(const color_hsv_t<T> &l, const color_hsv_t<U> &r)
	{
		return l.h == r.h && l.s == r.s && l.v == r.v;
	}

	template <typename T, typename U>
	static bool operator !=(const color_hsv_t<T> &l, const color_hsv_t<U> &r)
	{
		return !(l == r);
	}
}


#endif // math_color_h
