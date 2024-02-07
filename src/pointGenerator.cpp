#include "pointGenerator.hpp"

float randomFloat(float max)
{
	return (float)(rand()) / ((float)(RAND_MAX) / max);
}

Vector2* allocPoints(unsigned numberOfPoints) {
	Vector2* pointer = (Vector2*)malloc(sizeof(Vector2) * numberOfPoints);
	return pointer;
}

Vector2 randomCirclePosition(float circleSize) {
	Vector2 v{};
	float angle = randomFloat(M_PI * 2);
	float distance = randomFloat(circleSize);
	v.x = cos(angle) * distance;
	v.y = sin(angle) * distance;
	return v;
}

Vector2* generatePointsInCircle(float cirleSize, unsigned numberOfPoints, float distanceBetweenPoints)
{
	Vector2* pointer = allocPoints(numberOfPoints);
	if (pointer == NULL) {
		//TODO Handle err
		return NULL;
	}

	for (unsigned i = 0; i < numberOfPoints; i++) {
		Vector2 randomPos;
		while (1) {
			randomPos = randomCirclePosition(cirleSize);
			bool canBeUsed = true;
			for (unsigned x = 0; x < i; x++) {
				if (randomPos.getDistance(pointer[x]) <= distanceBetweenPoints) {
					canBeUsed = false;
					break;
				}
			}
			if (canBeUsed) break;
		}
		pointer[i] = randomPos;
	}

	return pointer;
}
