#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

#include "point.h"
#include "shape.h"

class Dot : public Shape {
public:
    Dot() : Shape("dot") {}

    Dot(std::string name) : Shape(name) {}

    Dot(double x, double y, double z, std::string name = "dot")
    : Shape({Point(x, y, z)}, name) {}

    Dot(Point point, std::string name = "dot") : Shape({point}, name) {}

    virtual ~Dot() {}

    virtual const bool operator==(const Shape& d) const override {
    	const bool t = d.type() == type();
    	const bool r = d.real[0] == real[0];
    	const bool m = d.medium == medium;
    	return t && r && m;
    }

    virtual const std::string to_string() const override {
    	if (real.empty()) {
    		return std::string("Dot()");
    	}

        std::string str = "Dot(";
        str += real[0].to_string();
        str += ")";
        return str;
    }

    virtual const Type2D type() const override {
        return Type2D::Dot;
    }
};

#endif  // DOT_H
