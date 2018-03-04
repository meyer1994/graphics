#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include <string>

typedef struct {
    double x;
    double y;
} Coordinate;

class Drawable {
public:
    Drawable(
        const std::vector<Coordinate>& points,
        const std::string name = "draw")
    : name(name),
      points(points) {}
        
    ~Drawable() {}

    std::string name;
	std::vector<Coordinate> points;
};

#endif  // DRAWABLE_H