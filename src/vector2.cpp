#include "vector2.h"

Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

float Vector2::getDistance(Vector2 vec)
{
	return sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y));
}

Vector2 Vector2::getVecInBetween(Vector2 vec)
{
	return Vector2((x + vec.x)/2, (y + vec.y)/2);
}

bool Vector2::operator==(Vector2 vec)
{
	return (x == vec.x && y == vec.y);
}

bool Vector2::operator!=(Vector2 vec)
{
	return !(x == vec.x && y == vec.y);
}