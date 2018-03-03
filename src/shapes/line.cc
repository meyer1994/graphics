#include "line.h"

Line::Line(const Point& a, const Point& b) :
	Drawable(std::vector<Point> {a, b}) {
	
}

Line::~Line() {}