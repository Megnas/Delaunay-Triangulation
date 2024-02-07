#include "line2.hpp"

Line2::Line2()
{
}

Line2::Line2(float _a, float _b, float _c) {
	a = _a;
	b = _b;
	c = _c;
}

Line2::Line2(Vector2 P, Vector2 Q) {
	a = Q.y - P.y;
	b = P.x - Q.x;
	c = a * P.x + b * P.y;
}

Line2 Line2::getPerpendicularBisector(Vector2 P) {
	Line2 line;

	line.c = -b * P.x + a * P.y;
	line.a = -b;
	line.b = a;

	return line;
}

Vector2 Line2::getIntersection(Line2 line)
{
	float determinant = a * line.b - line.a * b;

	float x = (line.b * c - b * line.c) / determinant;
	float y = (a * line.c - line.a * c) / determinant;

	return Vector2(x,y);
}
