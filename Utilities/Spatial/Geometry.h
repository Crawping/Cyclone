/* CHANGELOG
 * Written by Josh Grooms on 20151004
 */

#pragma once
#include "Array.h"
#include "UtilitiesAPI.h"
#include "Vertex.h"



namespace Geometry
{
	
	const Array<Vertex> Point = { Vertex() };
	/// <summary> A unit quad in the XY plane spanning the coordinates (0, 0, 0) to (1, 1, 0). </summary>
	/// <remarks> The vertices of this quad are not shared and are wound counter-clockwise. </remarks>
	const Array<Vertex> Quad =
	{
		Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	};

}
