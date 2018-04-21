#ifndef SHAPE3D_H
#define SHAPE3D_H

#include <set>
#include <vector>
#include <string>


#include "line.h"
#include "shape.h"
#include "point.h"


enum class Type3D { Polyhedron };


class Shape3D {
public:
	Shape3D() : name("shape3d") {}

	explicit Shape3D(std::string name) : name(name) {}

	Shape3D(std::vector<Line> ls, std::string name = "shape3d")
	: name(name), lines(ls) {}

	~Shape3D() {}

	const Point medium() const {
		Vector med{0, 0, 0};

		for (const Line& l : lines) {
			for (const Point& p : l.real) {
				for (int i = 0; i < 3; i++) {
					med[i] += p[i];
				}
			}
		}
		return Point(med);
	}

	void scale(double ratio) {
		for (Line& l : lines) {
			l.scale(ratio);
		}
	}

    void translate(double x, double y, double z) {
        for (Line& l : lines) {
        	l.translate(x, y, z);
        }
    }

    int size() const {
        return lines.size();
    }

    const Line& operator[](int i) const {
        return lines[i];
    }

    Line& operator[](int i) {
        return lines[i];
    }

    void transform(Matrix& m) {
        for (Line& l : lines) {
            l.transform(m);
        }
    }

	virtual const std::string to_string() const = 0;

	virtual const Type3D type() const = 0;

	std::string name;
	std::vector<Line> lines;
};


#endif  // SHAPE3D_H
