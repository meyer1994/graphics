#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include "point.h"

class Drawable {
public:
    Drawable() : points() {}
    explicit Drawable(std::vector<Point> points_in) : points(points_in) {}

    std::vector<Point> points;

    const Point get_medium_point() const {
        double medium_x = 0;
        double medium_y = 0;

        int total_points = points.size();

        for (Point p : points) {
            medium_x += p.x;
            medium_y += p.y;
        }

        medium_x /= total_points;
        medium_y /= total_points;

        return Point(medium_x, medium_y);
    }

    void move(double x, double y) {
        Point m = get_medium_point();
        for (Point& p : points) {
            p.x = p.x - m.x + x;
            p.y = p.y - m.y + y;
        }
    }

    void inflate(double s) {
        Point medium = get_medium_point();
        move(0, 0);
        scale(s);
        move(medium.x, medium.y);
    }

    void scale(double s) {
        for (Point& p : points) {
            p.x *= s;
            p.y *= s;
        }
    }

    void translate(double x, double y) {
        Point m = get_medium_point();
        move(m.x + x, m.y + y);
    }

};

#endif  // DRAWABLE_H