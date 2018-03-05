#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"

namespace Shape {

class Polygon : public Drawable {
public:
	explicit Polygon(std::vector<Point> points) : Drawable(points) {}
        
};

}  // namespace Shape

#endif  // POLYGON_H