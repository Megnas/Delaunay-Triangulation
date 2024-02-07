#include "triangle.hpp"

#include <iostream>

Triangle getSuperTriangle(Vector2* points, unsigned numberOfPoints)
{
    //Declare min and max variables
    Vector2 minPoint = points[0];
    Vector2 maxPoint = minPoint;

    //find lowest and highest point
    for (unsigned i = 1; i < numberOfPoints; i++) {
        if (points[i].x < minPoint.x) {
            minPoint.x = points[i].x;
        }
        else if (points[i].x > maxPoint.x) {
            maxPoint.x = points[i].x;
        }

        if (points[i].y < minPoint.y) {
            minPoint.y = points[i].y;
        }
        else if (points[i].y > maxPoint.y) {
            maxPoint.y = points[i].y;
        }
    }

    //Add increase
    //float xIncrease = (maxPoint.x - minPoint.x) * .1f;
    //float yIncrease = (maxPoint.y - minPoint.y) * .1f;

    minPoint.x -= 1;
    minPoint.y -= 1;
    maxPoint.x += 1;
    maxPoint.y += 1;

    //calculate width and height
    float width = maxPoint.x - minPoint.x;
    float height = maxPoint.y - minPoint.y;

    return Triangle{ Vector2{minPoint.x - width, minPoint.y}, Vector2{maxPoint.x + width, minPoint.y}, Vector2{(minPoint.x + maxPoint.x) / 2.f, maxPoint.y + height} };
}

Edge::Edge()
{
    x = Vector2();
    y = Vector2();
}

Edge::Edge(Vector2 a, Vector2 b)
{
    x = a;
    y = b;
}

bool Edge::operator==(Edge e)
{
    return (x == e.x && y == e.y) || (x == e.y && y == e.x);
}

bool Edge::operator!=(Edge e)
{
    return !((x == e.x && y == e.y) || (x == e.y && y == e.x));
}

Triangle::Triangle()
{
    a = Vector2(0, 0);
}

Triangle::Triangle(Vector2 _a, Vector2 _b, Vector2 _c)
{
    a = _a;
    b = _b;
    c = _c;
}

Vector2 Triangle::getCircumcenter()
{
    Line2 line1(a, b);
    Line2 line2(a, c);

    line1 = line1.getPerpendicularBisector(a.getVecInBetween(b));
    line2 = line2.getPerpendicularBisector(a.getVecInBetween(c));

    return line1.getIntersection(line2);
}

//Vector2 Triangle::getCircumcenter()
//{
//    Vector2 lA;
//    Vector2 lB;
//    Vector2 lC;
//
//    if (a.y == b.y) {
//        lA = a;
//        lB = c;
//        lC = b;
//    }
//    else if (b.y == c.y) {
//        lA = b;
//        lB = a;
//        lC = c;
//    }
//    else {
//        lA = a;
//        lB = b;
//        lC = c;
//    }
//
//    Vector2 sX{ (lA.x + lB.x) / 2, (lA.y + lB.y) / 2 };
//    Vector2 sY{ (lB.x + lC.x) / 2, (lB.y + lC.y) / 2 };
//
//    float mX;
//    if (lA.x - lB.x == 0) {
//        mX = 0;
//    }
//    else {
//        mX = 1 / (-(lA.y - lB.y) / (lA.x - lB.x));
//    }
//
//    float mY;
//    if (lB.x - lC.x == 0) {
//        mY = 0;
//    }
//    else {
//        mY = 1 / (-(lB.y - lC.y) / (lB.x - lC.y));
//    }
//
//    float X = (-mY * sY.x + sY.y + mX * sX.x - sX.y) / (mX - mY);
//    float Y = mX * (X - sX.x) + sX.y;
//    return Vector2{ X, Y };
//}

void Triangle::getEdges(Edge edgeBuffer[3])
{
    edgeBuffer[0] = Edge(a, b);
    edgeBuffer[1] = Edge(b, c);
    edgeBuffer[2] = Edge(c, a);
}

bool Triangle::contains(Vector2 point)
{
    return a == point || b == point || c == point;
}

TriangleC::TriangleC(Vector2 _a, Vector2 _b, Vector2 _c)
{
    triangle = Triangle(_a, _b, _c);
    circumcenter = triangle.getCircumcenter();
    std::cout << _a.getDistance(circumcenter) << "   " << _b.getDistance(circumcenter) << "   " << _c.getDistance(circumcenter) << "\n";
}

TriangleC::TriangleC(Triangle tri)
{
    triangle = tri;
    circumcenter = triangle.getCircumcenter();
}

bool TriangleC::liesInCircumcenter(Vector2 vec) {
    return circumcenter.getDistance(triangle.a) >= circumcenter.getDistance(vec);
}

bool TriangleC::operator==(TriangleC tri)
{
    return this == &tri;
}

bool operator==(TriangleC const& a, TriangleC const& b) {
    return &a == &b;
}

bool TriangleC::operator!=(TriangleC tri)
{
    return this != &tri;
}

bool TriangleC::operator==(TriangleC* tri)
{
    return this == tri;
}

bool TriangleC::operator!=(TriangleC* tri)
{
    return this != tri;
}
