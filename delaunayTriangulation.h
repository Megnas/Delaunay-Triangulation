#ifndef DELAUNAY_TRIANGULATION_HEADER
#define DELAUNAY_TRIANGULATION_HEADER

#include <list>
#include <algorithm>
#include "triangle.h"
#include "vector2.h"

std::list<TriangleC> triangulate(Vector2* points, unsigned numberOfPoints);

#endif // !DELAUNAY_TRIANGULATION_HEADER