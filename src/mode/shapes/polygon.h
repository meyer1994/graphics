#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include <vector>
#include <initializer_list>

#include "point.h"
#include "shape.h"

class Polygon : public Shape {
public:
    Polygon() : Shape("polygon") {}

    Polygon(std::string name) : Shape(name) {}

    Polygon(std::initializer_list<Point> d) : Shape(d, "polygon") {}

    Polygon(std::vector<Point> points, std::string name = "polygon")
    : Shape(points, name) {}

    virtual ~Polygon() {}

    virtual const std::string to_string() const override {
        if (real.empty()) {
            return "Polygon()";
        }

        std::string str = "Polygon(";
        for (int i = 0; i < real.size() - 1; i++) {
            const Point& p = real[i];
            str += p.to_string() + ", ";
        }
        const Point& p = real.back();
        str += p.to_string() + ")";

        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Polygon;
    }

    virtual const bool operator==(const Shape& p) const override {
    	if (p.type() != type()) {
    		return false;
    	}

    	if (p.real.size() != real.size()) {
    		return false;
    	}

    	for (int i = 0; i < real.size(); i++) {
    		if (p.real[i] != real[i]) {
    			return false;
    		}
    	}

    	return true;
    }

    bool filled = false;
};

#endif  // POLYGON_H
