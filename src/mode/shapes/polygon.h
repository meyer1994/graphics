#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>

#include "line.h"
#include "point.h"
#include "shape.h"

class Polygon : public Shape {
public:
    Polygon() : Shape(name = "polygon") {}

    explicit Polygon(std::string name) : Shape(name) {}

    Polygon(std::vector<Point> points, std::string name = "polygon")
    : Shape(name) {
    	// Add lines to shape
    	for (int i = 0; i < points.size(); i++) {
    		int k = (i + 1) % points.size();
    		Point a = points[i];
    		Point b = points[k];
    		Line l(a, b);
    		lines.push_back(l);
    	}

    	// Sum
    	for (const Line& l : lines) {
    		for (int i = 0; i < l.medium.size(); i++) {
	    		medium[i] += l.medium[i];
    		}
    	}

    	// Divide
    	for (double& d : medium) {
    		d /= lines.size();
    	}
    }

    virtual ~Polygon() {}

	virtual void transform(const Matrix& m) override {
		for (Line& l : lines) {
			l.transform(m);
		}

		medium.transform(m);
	}

    virtual const std::string to_string() const override {
        if (lines.size() == 0) {
            return "Polygon()";
        }

        std::string str = "Polygon(";
        for (int i = 0; i < lines.size() - 1; i++) {
            const Point& p = lines[i].a;
            str += p.to_string() + ", ";
        }
        const Point& p = lines.back().a;
        str += p.to_string() + ")";

        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Polygon;
    }

    virtual const bool operator==(const Polygon& p) const {
    	if (p.lines.size() != lines.size()) {
    		return false;
    	}

    	for (int i = 0; i < lines.size(); i++) {
    		if (lines[i] != p.lines[i])  {
    			return false;
    		}
    	}

    	return true;
    }

    virtual const bool operator!=(const Polygon& p) const {
    	return !(p == *this);
    }

    std::vector<Line> lines;
};

#endif  // POLYGON_H
