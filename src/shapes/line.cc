#include "line.h"

Line::Line(const std::string name, const Point& a, const Point& b) :
Drawable(name, std::vector<Point> {a, b})
{
	
}

Line::~Line() {}