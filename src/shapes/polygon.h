#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"

namespace Shape {

class Polygon : public Drawable {
public:
	Polygon(
        const std::vector<Coordinate> points,
        const std::string name = "polygon")
    : Drawable(points, name) {}
        
	~Polygon() {}
};

}  // namespace Shape

#endif  // POLYGON_H