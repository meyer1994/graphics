#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include <string>

#include "point.h"

class Drawable {
public:
	Drawable(const std::string name, const std::vector<Point>& points);
	~Drawable();

    std::string name;
	std::vector<Point> points;
};

#endif  // DRAWABLE_H