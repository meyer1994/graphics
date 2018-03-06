#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"

class Polygon : public Drawable {
public:
	explicit Polygon(std::vector<Point> points) : Drawable(points) {}
	
};

#endif  // POLYGON_H