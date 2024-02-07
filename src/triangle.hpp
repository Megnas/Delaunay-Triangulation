#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "vector2.hpp"
#include "line2.hpp"

class Edge {
public:
	Vector2 x;
	Vector2 y;
	Edge();
	Edge(Vector2 a, Vector2 b);
	bool operator==(Edge e);
	bool operator!=(Edge e);
};

class Triangle
{
public:
	Vector2 a;
	Vector2 b;
	Vector2 c;
	Triangle();
	Triangle(Vector2 _a, Vector2 _b, Vector2 _c);
	Vector2 getCircumcenter();
	void getEdges(Edge edgeBuffer[3]);
	bool contains(Vector2 point);
};

class TriangleC {
public:
	Triangle triangle;
	Vector2 circumcenter;
	TriangleC(Vector2 _a, Vector2 _b, Vector2 _c);
	TriangleC(Triangle tri);
	bool liesInCircumcenter(Vector2 vec);
	bool operator==(TriangleC tri);
	bool operator!=(TriangleC tri);
	bool operator==(TriangleC* tri);
	bool operator!=(TriangleC* tri);
};

Triangle getSuperTriangle(Vector2* points, unsigned numberOfPoints);

bool operator==(TriangleC const& a, TriangleC const& b);
#endif // !TRIANGLE_HEADER
