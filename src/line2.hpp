#ifndef LINE2_HEADER
#define LINE2_HEADER

#include "vector2.hpp"

class Line2 {
public:
	float a;
	float b;
	float c;
	Line2();
	Line2(float _a, float _b, float _c);
	Line2(Vector2 P, Vector2 Q);
	Line2 getPerpendicularBisector(Vector2 P);
	Vector2 getIntersection(Line2 line);
};

#endif // !LINE_HEADER

