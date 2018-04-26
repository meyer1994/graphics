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

	explicit Line(std::string name) : Shape(name) {}

	Line(Point a, Point b, std::string name = "line")
	: Shape(name), a(a), b(b) {
		if (a.size() != b.size()) {
			throw std::invalid_argument("Points must have same number of dimensions");
		}

		// Calculate medium point
		for (int i = 0; i < a.size(); i++) {
			double m = (a[i] + b[i]) / 2;
			medium[i] = m;
		}
	}

	virtual ~Line() {}

	virtual void transform(const Matrix& m) override {
		a.transform(m);
		b.transform(m);
		medium.transform(m);
	}

	virtual const std::string to_string() const override {
		std::string str = "Line(";
		str += a.to_string() + ", ";
		str += b.to_string() + ")";
		return str;
	}

	virtual const Type2D type() const override {
		return Type2D::Line;
	}

	virtual const bool operator==(const Line& l) const {
		bool pa = a == l.a;
		bool pb = b == l.b;

		return pa && pb;
	}

	virtual const bool operator!=(const Line& l) const {
		return !(l == *this);
	}

	// Real points
	Point a;
	Point b;

	// Window points
	Point aw;
	Point bw;
};

#endif  // LINE_H
