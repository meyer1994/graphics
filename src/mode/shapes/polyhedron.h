#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <set>
#include <vector>
#include <string>
#include <initializer_list>


#include "shape.h"
#include "point.h"
#include "vector.h"
#include "polygon.h"
#include "../transform.h"


class Polyhedron : public Shape {
public:
	Polyhedron() : Shape("polyhedron") {}

	Polyhedron(std::initializer_list<Polygon> d)
	: Shape("polyhedron"),
	  faces(d) {
	  	medium = calculate_medium();
	}

	Polyhedron(std::string name) : Shape(name) {}

	Polyhedron(std::vector<Polygon> faces, std::string name = "polyhedron")
	: Shape(name),
	  faces(faces) {
	  	medium = calculate_medium();
	  }

	virtual ~Polyhedron() {}

	// virtual void rotate(const double x, const double y, const double z) {
	// 	const Matrix rx = Transform::rotatex(x);
	// 	const Matrix ry = Transform::rotatey(y);
	// 	const Matrix rz = Transform::rotatez(z);

	// 	const Matrix r = rx * ry * rz;
	// 	transform(r);
	// }

	// virtual void rotate(const double angle, const Vector& v) {
	// 	const Matrix r = Transform::rotate(angle, v);
	// 	transform(r);
	// }

	// virtual void scale(double ratio) {
	// 	const Matrix s = Transform::scale(ratio);
	// 	transform(s);
	// }

	// virtual void inflate(double ratio) {
	// 	const Matrix t0 = Transform::translate(-medium);
	// 	const Matrix s = Transform::scale(ratio);
	// 	const Matrix t1 = Transform::translate(medium);
	// 	transform(t0 * s * t1);
	// }

    // virtual void translate(double x, double y, double z) {
    // 	const Matrix t = Transform::translate(x, y, z);
    // 	transform(t);
    // }

    virtual void transform(const Matrix& m) override {
        for (Polygon& p : faces) {
            p.transform(m);
        }
        medium.transform(m);
    }

	virtual const std::string to_string() const override {
		if (faces.empty()) {
			return std::string("Polyhedron()");
		}

		std::string str = "Polyhedron(";
		for (int i = 0; i < faces.size() - 1; i++) {
			const Polygon& p = faces[i];
			str += p.to_string() + ", ";
		}
		const Polygon& last = faces.back();
		str += last.to_string() + ")";

		return str;
	}

	virtual const Type2D type() const {
		return Type2D::Polyhedron;
	}

	std::vector<Polygon> faces;

protected:
	virtual const Point calculate_medium() override {
		Vector m{0, 0, 0};
		for (Polygon& p : faces) {
			m = m + p.medium;
		}
		m = m / faces.size();
		return Point(m);
	}
};


#endif  // POLYHEDRON_H
