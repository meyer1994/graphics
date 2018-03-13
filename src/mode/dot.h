#ifndef DOT_H
#define DOT_H

#include "drawable.h"

class Dot : public Drawable {
public:
    Dot() : Drawable() {}

    Dot(const double x, const double y)
    : Drawable(),
      point(x, y) {}

    Dot(const double x, const double y, const double z)
    : Drawable(),
      point(x, y, z) {}

    const Point medium() const override {
        return Point(point);
    }

    void transform(const Matrix& m) override {
        point = p_multiply(point, m);
    }

    void scale(const double& ratio) {
        // nothing
    }

    void translate(const double& x, const double& y) {
        transform(translate_matrix(std::vector<double>{x, y}));
    }

    void rotate(const double& angle) {
        transform(rotate_matrix(point.size() - 1, angle));
    }

    const std::string to_string() const override {
        if (point.size() == 0) {
            return "Dot()";
        }

        std::string str = "Dot(";
        str.append(point.to_string());
        str.append(")");
        return str;
    }

    Point point;
};

#endif  // DOT_H
