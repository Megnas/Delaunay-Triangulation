#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

#include <cmath>

class Vector2 {
public:
	float x;
	float y;
	Vector2();
	Vector2(float _x, float _y);
	float getDistance(Vector2 vec);
	Vector2 getVecInBetween(Vector2 vec);
	bool operator== (Vector2 vec);
	bool operator!= (Vector2 vec);
};
#endif // VECTOR2_HEADER
