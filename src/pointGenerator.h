#ifndef POINT_GENERATOR_HEADER
#define POINT_GENERATOR_HEADER

#include "vector2.h"

#define M_PI 3.14159265358979323846f

#include <iostream>
#include <stdlib.h>
#include <cmath>

Vector2* generatePointsInCircle(float cirleSize, unsigned numberOfPoints, float distanceBetweenPoints);

#endif // !POINT_GENERATOR_HEADER