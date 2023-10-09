#include "delaunayTriangulation.h"

#include "iostream"

std::list<TriangleC> triangulate(Vector2* points, unsigned numberOfPoints)
{
	//Init triangle list
	std::list<TriangleC> triangleList;

	//Add super triangle to list
	Triangle superTriangle = getSuperTriangle(points, numberOfPoints);
	triangleList.push_back(TriangleC(superTriangle));

	//Loop trought all points
	for (unsigned currentPointIndex = 0; currentPointIndex < numberOfPoints; currentPointIndex++) {
		//Init bad triangle list
		std::list<std::list<TriangleC>::iterator> badTriangles;

		//Loop trough all triangles and found bad ones
		for (std::list<TriangleC>::iterator i = triangleList.begin(); i != triangleList.end(); i++) {
			if (i->liesInCircumcenter(points[currentPointIndex])) {
				badTriangles.push_back(i);

			}
		}

		std::cout << currentPointIndex << ": " << badTriangles.size() << " bad triangles found\n";

		//Create poligion
		std::list<Edge> poligonList;
		std::list<Edge> badPoligons;
		Edge edgeBuffer[3];
		for (std::list<TriangleC>::iterator i : badTriangles) {
			i->triangle.getEdges(edgeBuffer);
			for (int edgeId = 0; edgeId < 3; edgeId++) {
				//Check if is not already in bad poligons
				if (std::find(badPoligons.begin(), badPoligons.end(), edgeBuffer[edgeId]) == badPoligons.end()) {
					std::list<Edge>::iterator itr = std::find(poligonList.begin(), poligonList.end(), edgeBuffer[edgeId]);
					if (itr == poligonList.end()) { //edge is not in poligon, must be added
						poligonList.push_back(edgeBuffer[edgeId]);
					}
					else { //edge is in poligon, must be removed
						poligonList.erase(itr);
						badPoligons.push_back(edgeBuffer[edgeId]);
					}
				}
			}
		}

		//Remove bad triangles
		for (std::list<TriangleC>::iterator i : badTriangles) {
			triangleList.erase(i);
		}

		//Triangulate Poligon
		for (std::list<Edge>::iterator i = poligonList.begin(); i != poligonList.end(); i++) {
			TriangleC newTriangle(i->x, i->y, points[currentPointIndex]);
			triangleList.push_back(newTriangle);
		}

		std::cout << currentPointIndex << "   " << triangleList.size() << "\n";

		//if (currentPointIndex == 0) break;
	}

	//Find triangles that contains parts of supertriangle
	std::list<std::list<TriangleC>::iterator> trianglesToRemove;
	for (std::list<TriangleC>::iterator i = triangleList.begin(); i != triangleList.end(); i++) {
		if (i->triangle.contains(superTriangle.a) || i->triangle.contains(superTriangle.b) || i->triangle.contains(superTriangle.c)) {
			trianglesToRemove.push_back(i);
		}
	}

	for (std::list<TriangleC>::iterator i : trianglesToRemove) {
		triangleList.erase(i);
	}

	return triangleList;
}

//std::list<TriangleC> triangulate(Vector2* points, unsigned numberOfPoints)
//{
//	std::list<TriangleC> triangleList;
//
//	//Add super triangle to list
//	triangleList.push_back(TriangleC(getSuperTriangle(points, numberOfPoints)));
//
//	for (unsigned currentPointIndex = 0; currentPointIndex < numberOfPoints; currentPointIndex++) {
//		std::list<TriangleC*> badTriangles;
//		//Find all bad triangles
//		for (TriangleC triangle : triangleList) {
//			if (triangle.circumcenter.getDistance(triangle.triangle.a) >= triangle.circumcenter.getDistance(points[currentPointIndex])) {
//				badTriangles.push_back(&triangle);
//			}
//		}
//
//		//Find all unique edges in bad triangles
//		std::list<Edge> poligonList;
//		Edge edgeBuffer[3];
//		for(TriangleC* const& triangle : badTriangles) {
//			triangle->triangle.getEdges(edgeBuffer);
//			for (unsigned i = 0; i < 3; i++) {
//				poligonList.push_back(edgeBuffer[i]);
//			}
//		}
//		poligonList.unique();
//
//		//Remove bad triangles from list
//		for (TriangleC* const& triangle : badTriangles) {
//			triangleList.remove(*triangle);
//		}
//
//		//Create new triangles
//		for (Edge const& e : poligonList) {
//			triangleList.push_back(TriangleC(e.x, e.y, points[currentPointIndex]));
//		}
//	}
//
//	std::list<TriangleC*> superTriangleLeftOvers;
//	for (TriangleC const& triangle : triangleList) {
//
//	}
//
//	return triangleList;
//}