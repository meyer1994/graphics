#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

#include "point.h"

class Drawable {
public:
	Drawable(const std::vector<Point>& points);
	~Drawable();

	std::vector<Point> points;
};

#endif  // DRAWABLE_H