/* CHANGELOG
 * Written by Josh Grooms on 20160706 
 */

#pragma once
#include "Entity3D.h"
#include "Geometry.h"



class Point3D : public Entity3D
{
	public:
		Point3D() : Entity3D(Geometry::Point) { }
};