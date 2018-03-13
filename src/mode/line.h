#ifndef LINE_H
#define LINE_H

#include <vector>
#include <string>

#include "drawable.h"

class Line : public Drawable {
public:
    Line() : Drawable() {}

    Line(Point a, Point b)
    : Drawable(),
      a(a),
      b(b) {}
    
    const Point medium() const override {
        std::vector<double> medium_point;
        for (int i = 0; i < a.size() - 1; i++) {
            double m = (a[i] + b[i]) / 2;
            medium_point.push_back(m);
        }
        return Point(medium_point);
    }

    void translate(const double x, const double y) {
        Matrix t = translate_matrix(std::vector<double>{x, y});
        transform(t);
    }

    void scale(const double& ratio) {
        Matrix s = scale_matrix(std::vector<double>(a.size() - 1, ratio));
        transform(s);
    }

    void rotate(const double& angle) {
        Matrix r = rotate_matrix(a.size() - 1, angle);
        transform(r);
    }

    void transform(const Matrix& m) {
        a = p_multiply(a, m);
        b = p_multiply(b, m);
    }

    const std::string to_string() const override {
        if (a.size() == 0 || b.size() == 0) {
            return "Line()";
        }

        std::string s = "Line(";
        s.append(a.to_string());
        s.append(", ");
        s.append(b.to_string());
        s.append(")");
        return s;
    }

    Point a;
    Point b;
};

#endif  // LINE_H