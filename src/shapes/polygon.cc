#include "polygon.h"

Shape::Polygon::Polygon(const std::string name, std::vector<Point> points) :
Drawable(name, points)
{

}

Shape::Polygon::~Polygon() {}
