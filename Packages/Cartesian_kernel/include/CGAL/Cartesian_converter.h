// ============================================================================
//
// Copyright (c) 2001 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : include/CGAL/Cartesian_converter.h
// revision      : $Revision$
// revision_date : $Date$
// package       : Cartesian_kernel
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//                 Menelaos Karavelas <mkaravel@cse.nd.edu>
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
//
// ============================================================================

#ifndef CGAL_CARTESIAN_CONVERTER_H
#define CGAL_CARTESIAN_CONVERTER_H

// This file contains the definition of a kernel converter, based on Cartesian
// representation.  It should work between *Cartesian<A> and *Cartesian<B>,
// provided you give a NT converter from A to B.
// There's a Homogeneous counterpart.

#include <CGAL/basic.h>
#include <CGAL/NT_converter.h>
#include <CGAL/Enum_converter.h>

CGAL_BEGIN_NAMESPACE

template < class K1, class K2,
           class Converter = NT_converter<typename K1::FT, typename K2::FT> >
class Cartesian_converter : public Enum_converter
{
public:
    typedef K1         Source_kernel;
    typedef K2         Target_kernel;
    typedef Converter  Number_type_converter;

    Cartesian_converter()
	: c(), k() {}

    typename K2::Point_2
    operator()(const typename K1::Point_2 &a) const
    {
        typedef typename K2::Point_2 Point_2;
	return Point_2(c(a.x()), c(a.y()));
    }

    typename K2::Vector_2
    operator()(const typename K1::Vector_2 &a) const
    {
        typedef typename K2::Vector_2  Vector_2;
	return Vector_2(c(a.x()), c(a.y()));
    }

    typename K2::Direction_2
    operator()(const typename K1::Direction_2 &a) const
    {
        typedef typename K2::Direction_2  Direction_2;
	return Direction_2(c(a.dx()), c(a.dy()));
    }

    typename K2::Segment_2
    operator()(const typename K1::Segment_2 &a) const
    {
        typedef typename K2::Segment_2  Segment_2;
	return Segment_2(operator()(a.source()), operator()(a.target()));
    }

    typename K2::Line_2
    operator()(const typename K1::Line_2 &a) const
    {
        typedef typename K2::Line_2 Line_2;
	return Line_2(c(a.a()), c(a.b()), c(a.c()));
    }

    typename K2::Ray_2
    operator()(const typename K1::Ray_2 &a) const
    {
        typedef typename K2::Ray_2  Ray_2;
	return Ray_2(operator()(a.source()), operator()(a.second_point()));
    }

    typename K2::Circle_2
    operator()(const typename K1::Circle_2 &a) const
    {
        typedef typename K2::Circle_2  Circle_2;
	return Circle_2(operator()(a.center()),
		        c(a.squared_radius()),
			a.orientation());
    }

    typename K2::Triangle_2
    operator()(const typename K1::Triangle_2 &a) const
    {
        typedef typename K2::Triangle_2  Triangle_2;
	return Triangle_2(operator()(a.vertex(0)),
		          operator()(a.vertex(1)),
		          operator()(a.vertex(2)));
    }

    typename K2::Iso_rectangle_2
    operator()(const typename K1::Iso_rectangle_2 &a) const
    {
        typedef typename K2::Iso_rectangle_2  Iso_rectangle_2;
	return Iso_rectangle_2(operator()(a.min()), operator()(a.max()));
    }


    typename K2::Point_3
    operator()(const typename K1::Point_3 &a) const
    {
        typedef typename K2::Point_3 Point_3;
	return Point_3(c(a.x()), c(a.y()), c(a.z()));
    }

    typename K2::Vector_3
    operator()(const typename K1::Vector_3 &a) const
    {
        typedef typename K2::Vector_3  Vector_3;
	return Vector_3(c(a.x()), c(a.y()), c(a.z()));
    }

    typename K2::Direction_3
    operator()(const typename K1::Direction_3 &a) const
    {
        typedef typename K2::Direction_3  Direction_3;
	return Direction_3(c(a.dx()), c(a.dy()), c(a.dz()));
    }

    typename K2::Segment_3
    operator()(const typename K1::Segment_3 &a) const
    {
        typedef typename K2::Segment_3  Segment_3;
	return Segment_3(operator()(a.source()), operator()(a.target()));
    }

    typename K2::Line_3
    operator()(const typename K1::Line_3 &a) const
    {
        typedef typename K2::Line_3  Line_3;
	return Line_3(operator()(a.point()), operator()(a.direction()));
    }

    typename K2::Ray_3
    operator()(const typename K1::Ray_3 &a) const
    {
        typedef typename K2::Ray_3 Ray_3;
	return Ray_3(operator()(a.source()), operator()(a.second_point()));
    }

    typename K2::Sphere_3
    operator()(const typename K1::Sphere_3 &a) const
    {
        typedef typename K2::Sphere_3  Sphere_3;
	return Sphere_3(operator()(a.center()),
		        c(a.squared_radius()),
			a.orientation());
    }

    typename K2::Triangle_3
    operator()(const typename K1::Triangle_3 &a) const
    {
        typedef typename K2::Triangle_3  Triangle_3;
	return Triangle_3(operator()(a.vertex(0)),
		          operator()(a.vertex(1)),
		          operator()(a.vertex(2)));
    }

    typename K2::Tetrahedron_3
    operator()(const typename K1::Tetrahedron_3 &a) const
    {
        typedef typename K2::Tetrahedron_3  Tetrahedron_3;
	return Tetrahedron_3(operator()(a.vertex(0)),
		             operator()(a.vertex(1)),
		             operator()(a.vertex(2)),
		             operator()(a.vertex(3)));
    }

    typename K2::Plane_3
    operator()(const typename K1::Plane_3 &a) const
    {
        typedef typename K2::Plane_3  Plane_3;
	return Plane_3(c(a.a()), c(a.b()), c(a.c()), c(a.d()));
    }

    typename K2::Iso_cuboid_3
    operator()(const typename K1::Iso_cuboid_3 &a) const
    {
        typedef typename K2::Iso_cuboid_3 Iso_cuboid_3;
	return Iso_cuboid_3(operator()(a.min()), operator()(a.max()));
    }

private:
    Converter c;
    K2 k;
};

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_CONVERTER_H
