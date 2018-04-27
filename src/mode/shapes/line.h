#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>
#include <stdexcept>

#include "point.h"
#include "shape.h"

class Line : public Shape {
public:
	Line() : Shape(name = "line") {}

	Line(std::string name) : Shape(name) {}

	Line(Point a, Point b, std::string name = "line")
	: Shape({a, b}, name) {
		if (a.size() != b.size()) {
			throw std::invalid_argument("Points must have same number of dimensions");
		}
	}

	virtual ~Line() {}

	virtual const std::string to_string() const override {
		if (real.empty()) {
			return std::string("Line()");
		}

		std::string str = "Line(";
		str += real[0].to_string() + ", ";
		str += real[1].to_string() + ")";
		return str;
	}

	virtual const Type2D type() const override {
		return Type2D::Line;
	}
};

#endif  // LINE_H
