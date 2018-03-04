#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"

namespace Shape {

class Polygon : public Drawable {
public:
	Polygon(const std::string name, std::vector<Point> points);
	~Polygon();
};

}  // namespace Shape

#endif  // POLYGON_H