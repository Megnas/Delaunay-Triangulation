#ifndef DELAUNAY_TRIANGULATION_HEADER
#define DELAUNAY_TRIANGULATION_HEADER

#include <list>
#include <algorithm>
#include "triangle.hpp"
#include "vector2.hpp"

std::list<TriangleC> triangulate(Vector2* points, unsigned numberOfPoints);

#endif // !DELAUNAY_TRIANGULATION_HEADER
