#define BOOST_TEST_MODULE math test
#include <boost/test/unit_test.hpp>

#include <src/math.h>


BOOST_AUTO_TEST_CASE( point_2d )
{
	math::setup<math::math_t>();

	math::point_2d p0(math::point_2d::o);

	BOOST_CHECK( is_zero(p0) );

	math::point_2d p1(math::make_p( 1,  1));
	math::point_2d p2(math::make_p(-1, -1));

	BOOST_CHECK( !is_zero(p1) );
	BOOST_CHECK( !is_zero(p2) );
}

BOOST_AUTO_TEST_CASE( lines )
{
	math::setup<math::math_t>();

	{
	math::point_2d p0(-1, -1);
	math::vector_2d v1( 1,  1);

	math::line_2d l(p0, v1);
	math::ray_2d r(p0, v1);
	}

	{
	math::point_2d p0(-1, -1);
	math::point_2d p1( 1,  1);

	math::line_2d l(p0, p1);
	math::line_segment_2d ls(p0, p1);
	}
}

BOOST_AUTO_TEST_CASE( matrix_3d )
{
	math::setup<math::math_t>();

	math::vector_3d f0(math::vector_3d::forward);
	math::vector_3d d0(math::vector_3d::forward);
	d0.x += 0.1f; d0.normalize();

	math::matrix_3d_t m0;
	math::look(m0, d0);

	math::vector_3d r0(m0 * f0);

	BOOST_CHECK(r0 == d0);

	math::quaternion_t q0;
	math::matrix_to_q(m0, q0);

	BOOST_CHECK(math::is_one(q0.length()));

	math::matrix_3d_t m1;
	math::rotation_to_m(q0, m1);

	BOOST_CHECK(m1 == m0);

	r0 = q0 ^ f0;

	BOOST_CHECK(r0 == d0);
}

BOOST_AUTO_TEST_CASE( matrix_3d_multiplication )
{
	math::matrix_3d_t tm_x; math::translation_to_m(math::vector_3d(10, 0, 0), tm_x);
	math::matrix_3d_t tm_y; math::translation_to_m(math::vector_3d(0, 10, 0), tm_y);
	math::matrix_3d_t tm_z; math::translation_to_m(math::vector_3d(0, 0, 10), tm_z);
	math::matrix_3d_t rm_x; math::rotation_to_m(math::quaternion_t(math::vector_3d::ox, 90 * math::degrees), rm_x);
	math::matrix_3d_t rm_y; math::rotation_to_m(math::quaternion_t(math::vector_3d::oy, 90 * math::degrees), rm_y);
	math::matrix_3d_t rm_z; math::rotation_to_m(math::quaternion_t(math::vector_3d::oz, 90 * math::degrees), rm_z);

	math::point_3d v_z = rm_x*tm_y*math::point_3d::o;
	math::point_3d v_x = rm_y*tm_z*math::point_3d::o;
	math::point_3d v_y = rm_z*tm_x*math::point_3d::o;

	BOOST_CHECK(v_x == math::vector_3d(10, 0, 0));
	BOOST_CHECK(v_y == math::vector_3d(0, 10, 0));
	BOOST_CHECK(v_z == math::vector_3d(0, 0, 10));
}

BOOST_AUTO_TEST_CASE( quaternion )
{
	math::setup<math::math_t>();

	math::vector_3d f0(math::vector_3d::forward);
	
	math::quaternion_t q0(math::vector_3d::up, 5 * math::degrees);

	BOOST_CHECK( q0.magnitude() == 1 );

	math::vector_3d rq0 = q0 ^ f0;

	BOOST_CHECK(rq0.y == 0);

	math::matrix_3d_t m0;
	math::rotation_to_m(q0, m0);

	math::vector_3d rm0 = m0 * f0;

	BOOST_CHECK(rm0.y == 0);

	BOOST_CHECK(rq0 == rm0);

	math::matrix_3d_t m1;
	math::look(m1, rq0);

	BOOST_CHECK(m1 == m0);
}

BOOST_AUTO_TEST_CASE( quaternion_multiplication )
{
	math::setup<math::math_t>();

	math::quaternion_t rq_x(math::vector_3d::ox, 15 * math::degrees);
	math::quaternion_t rq_y(math::vector_3d::oy, 90 * math::degrees);
	math::quaternion_t rq_z(math::vector_3d::oz, 90 * math::degrees);

	math::vector_3d vz = rq_x ^ math::vector_3d::oy;
	math::quaternion_t rq_u(vz, 180 * math::degrees);

	math::vector_3d vx = math::quaternion_t(rq_u * rq_x) ^ math::vector_3d::oz;

	math::quaternion_t rq_s = rq_x; rq_s *= rq_u;
	math::vector_3d vx2 = rq_s ^ math::vector_3d::oz;

	math::vector_3d vx3 = math::quaternion_t(rq_x * rq_u) ^ math::vector_3d::oz;
}

BOOST_AUTO_TEST_CASE( qua_qua )
{
	math::setup<math::math_t>();

	math::matrix_3d_t m; math::look(m, math::vector_3d(1, 1, 0).norm(), math::vector_3d::oz);

	math::vector_3d up1 = (m * math::vector_3d::up).norm();
	BOOST_CHECK(up1 == math::vector_3d::oz);

	math::quaternion_t q; math::matrix_to_q(m, q);
	BOOST_CHECK(q.magnitude() == 1);

	math::vector_3d up2 = (q ^ math::vector_3d::up).norm();
	BOOST_CHECK(up2 == math::vector_3d::oz);

	math::matrix_3d_t mv; math::rotate(q, mv);
	math::vector_3d up3 = (mv * math::vector_3d::up).norm();
	BOOST_CHECK(up3 == math::vector_3d::oz);
}

BOOST_AUTO_TEST_CASE( angle )
{
	math::setup<math::math_t>();

	{
	math::math_t a;

	a = math::angle(math::vector_2d::oy);

	BOOST_CHECK(a == 0.5f);

	a = math::angle(math::vector_2d::up, math::vector_2d::right);

	BOOST_CHECK(a == 0.5f);

	math::vector_2d v1(0, 1);
	math::vector_2d v2(1, 0);

	a = math::angle(v1, v2);

	BOOST_CHECK(a == 0.5f);

	a = math::angle(v2, v1);

	BOOST_CHECK(a == -0.5f);
	}
}

BOOST_AUTO_TEST_CASE( distance_2d )
{
	math::setup<math::math_t>();

	{
	math::point_2d p1(0, 0);
	math::point_2d p2(0, 1);
	math::math_t r = math::distance(p1, p2);

	BOOST_CHECK(r == 1);
	}

	{
	math::point_2d p1(0, 0);
	math::line_2d l2(math::make_p(1.f, -1.f), math::make_p(1.f, 1.f));
	math::math_t r = math::distance(p1, l2);

	BOOST_CHECK(r == -1);
	}

	{
	math::point_2d p1(0, 0), pa(1, 1), pb(-1, 1);
	math::line_segment_t<math::point_2d> l2(pa, pb);
	math::math_t r = math::distance(p1, l2);

	BOOST_CHECK(r == -1);
	}
}

BOOST_AUTO_TEST_CASE( frustrum )
{
	math::setup<math::math_t>();

	math::frustrum<math::math_t> f(60.f * math::degrees, 1920.f/1200.f, 0.5f, 100.5f);

	math::math_t gc = math::contains(math::point_3d(0, 0, 50.5f), f);

	BOOST_CHECK(gc == 50.f);

	math::math_t fc = math::contains(math::point_3d(10.f, 0, 0.5f), f);

	BOOST_CHECK(fc == 0);
}

BOOST_AUTO_TEST_CASE( interscetion_2d )
{
	math::setup<math::math_t>();

	{
	math::line_2d l1(math::make_p(0.f, 0.f), math::make_p(1.f, 1.f));
	math::line_2d l2(math::make_p(0.f, 1.f), math::make_p(1.f, 0.f));
	math::point_2d r = math::intersection(l1, l2);

	BOOST_CHECK(r == math::make_p(0.5f, 0.5f));
	}

	{
	math::line_2d l1(math::make_p(0.f, 0.f), math::make_p(0.f, 1.f));
	math::line_2d l2(math::make_p(1.f, 1.f), math::make_p(1.f, 0.f));
	math::point_2d r = math::intersection(l1, l2);

	BOOST_CHECK(is_null(r));
	}

	{
	math::circle c(1.f);
	math::line_2d l(math::make_p(1.f, 0.f), math::make_p(1.f, 1.f));
	math::line_segment_2d r = math::intersection(c, l);

	BOOST_CHECK(r.a() == math::make_p(1.f, 0.f));
	}
}

BOOST_AUTO_TEST_CASE( interscetion_3d )
{
	math::setup<math::math_t>();

	{
	math::line_3d l = math::ray_3d::ox;
	math::plane_t p = math::plane_t::ox;
	math::point_3d r = math::intersection(l, p);

	BOOST_CHECK(is_zero(r));
	}

	{
	math::line_3d l = math::ray_3d::ox;
	math::line_3d p = math::ray_3d::oy;
	math::line_segment_3d r = math::intersection(l, l);

	BOOST_CHECK(is_zero(r.a()));
	}

	{
	math::sphere s(1.f);
	math::plane_t p = math::plane_t::ox;
	math::point_3d r = math::intersection(s, p);

	BOOST_CHECK(is_zero(r));
	}
}

BOOST_AUTO_TEST_CASE( graph )
{
	math::setup<math::math_t>();

	math::graph_t<math::point_2d> g;

	auto i0 = g.insert(math::point_2d::o);

	BOOST_CHECK(g.size() == 1);

	auto i1 = g.insert(math::point_2d( 1,  1));
	auto i2 = g.insert(math::point_2d( 1, -1));
	auto i3 = g.insert(math::point_2d(-1, -1));
	auto i4 = g.insert(math::point_2d(-1,  1));

	BOOST_CHECK(g.size() == 5);

	g.link(i0, i1);
	g.link(i0, i2);
	g.link(i0, i3);
	g.link(i0, i4);
	g.link(i1, i2);
	g.link(i2, i3);
	g.link(i3, i4);
	g.link(i4, i1);
}

/*

BOOST_AUTO_TEST_CASE( delaunay )
{
	math::setup<math::math_t>();

	math::mesh_t<math::point_2d> m;
	math::aabb_2d ma(math::vector_2d(100.f, 100.f));
	math::mesh_t<math::point_2d>::set_type &ms = m;
	math::mesh_t<math::point_2d>::set_type::iterator
		ai = ms.insert(ma.a),
		bi = ms.insert(ma.ab()),
		ci = ms.insert(ma.b),
		di = ms.insert(ma.ba());
	m.insert(ai, bi, ci);
	m.insert(ai, ci, di);

	{
	math::delaunay_t<math::point_2d> d(m);

	d.insert(math::point_2d::o);
	}

	{
	math::set_t<math::point_2d> pts;
	pts.insert(ma.a);
	pts.insert(ma.ab());
	pts.insert(math::point_2d(-90.f, -90.f));
	pts.insert(math::point_2d(-40.f, -40.f));
	pts.insert(math::point_2d(  0.f,   0.f));
	pts.insert(math::point_2d( 40.f,  40.f));
	pts.insert(math::point_2d( 90.f,  90.f));
	pts.insert(ma.b);
	pts.insert(ma.ba());

	math::delaunay_t<math::point_2d> d(pts.begin(), pts.end());
	}
}

BOOST_AUTO_TEST_CASE( voronoi )
{
	math::setup<math::math_t>();

	{
	math::mesh_t<math::point_2d> m;
	math::aabb_2d ma(math::vector_2d(100.f, 100.f));
	math::set_t<math::point_2d> pts;
	pts.insert(ma.a);
	pts.insert(ma.ab());
	pts.insert(math::point_2d(-90.f, -90.f));
	pts.insert(math::point_2d(-40.f, -40.f));
	pts.insert(math::point_2d(  0.f,   0.f));
	pts.insert(math::point_2d( 40.f,  40.f));
	pts.insert(math::point_2d( 90.f,  90.f));
	pts.insert(ma.b);
	pts.insert(ma.ba());

	math::voronoi_t<math::point_2d> v(pts.begin(), pts.end());
	}
}

*/
