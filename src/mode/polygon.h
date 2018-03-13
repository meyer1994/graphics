#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"

class Polygon : public Drawable {
public:
    Polygon() : Drawable(), points() {}

	explicit Polygon(std::vector<Point> points) : Drawable(), points(points) {}

    const Point medium() const override {
        Point medium(points[0].size() - 1, 0);

        // Sum
        for (const Point& p : points) {
            for (int i = 0; i < p.size(); i++) {
                medium[i] += p[i];
            }
        }

        // Divide
        for (double& d : medium) {
            d /= points.size();
        }

        return medium;
    }

    void scale(const double& ratio) {
        std::vector<double> r(points[0].size() - 1, ratio);
        transform(scale_matrix(r));
    }

    void translate(const double& x, const double& y) {
        std::vector<double> t{x, y};
        transform(translate_matrix(t));
    }

    void transform(const Matrix& m) {
        for (Point& p : points) {
            p = p_multiply(p, m);
        }
    }

    void rotate(const double& angle) {
        std::cout << "nice" << std::endl;
        int dim = points[0].size() - 1;
        std::cout << "nice" << std::endl;
        transform(rotate_matrix(dim, angle));
    }

    const std::string to_string() const override {
        int total = points.size();
        std::string str = "Polygon(";
        for (int i = 0; i < total - 1; i++) {
            str.append(points[i].to_string());
            str.append(", ");
        }

        str.append(points[total - 1].to_string());
        str.append(")");

        return str;
    }

    std::vector<Point> points;
};

#endif  // POLYGON_H