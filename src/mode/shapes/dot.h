#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>

#include "point.h"
#include "shape.h"

class Dot : public Shape {
public:
    Dot() : Shape({Point(0, 0, 0)}, "dot") {}

    Dot(std::string name) : Shape({Point(0, 0, 0)}, name) {}

    Dot(double x, double y, double z, std::string name = "dot")
    : Shape({Point(x, y, z)}, name) {}

    Dot(Point point, std::string name = "dot") : Shape({point}, name) {}

    virtual ~Dot() {}

    virtual void inflate(const double ratio) override {
    	// Nothing
    	return;
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

    virtual const ShapeType type() const override {
        return ShapeType::Dot;
    }
};

#endif  // DOT_H
