#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "drawable.h"

namespace Shape {

class Polygon : public Drawable {
public:
	Polygon(std::vector<Point> points);
	~Polygon();
};

}  // namespace Shape

#endif  // POLYGON_H