#include "drawable.h"

Drawable::Drawable(const std::string name, const std::vector<Point>& points) :
name(name),
points(points)
{
	
}

Drawable::~Drawable() {}