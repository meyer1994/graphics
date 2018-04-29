#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <set>
#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>

#include "point.h"
#include "vector.h"
#include "polygon.h"
#include "base_shape.h"
#include "../transform.h"


class Polyhedron : public BaseShape {
public:
	Polyhedron() : BaseShape("polyhedron") {}

	Polyhedron(std::initializer_list<Polygon> d)
	: BaseShape("polyhedron"),
	  faces(d) {
	  	medium = calculate_medium();
	}

	Polyhedron(std::string name) : BaseShape(name) {}

	Polyhedron(std::vector<Polygon> faces, std::string name = "polyhedron")
	: BaseShape(name),
	  faces(faces) {
	  	if (faces.size() < 4) {
	  		throw std::invalid_argument("Polyhedron must have, at least, 4 faces");
	  	}
	  	medium = calculate_medium();
	}

	virtual ~Polyhedron() {}

	virtual void rotate(const double x, const double y, const double z) {
		const Matrix rx = Transform::rotatex(x);
		const Matrix ry = Transform::rotatey(y);
		const Matrix rz = Transform::rotatez(z);

		const Matrix r = rx * ry * rz;
		transform(r);
	}

	virtual void rotate(const double angle, const Vector& v) {
		const Matrix r = Transform::rotate(angle, v);
		transform(r);
	}

	virtual void scale(double ratio) {
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		transform(s);
	}

	virtual void inflate(double ratio) {
		const Matrix t0 = Transform::translate(-medium);
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		const Matrix t1 = Transform::translate(medium);
		transform(t0 * s * t1);
	}

    virtual void translate(double x, double y, double z) {
    	const Matrix t = Transform::translate(x, y, z);
    	transform(t);
    }

    virtual void transform(const Matrix& m) {
    	for (Polygon& p : faces) {
    		p.transform(m);
    	}
    	medium.transform(m);
    }

    virtual void w_transform(const Matrix& m) {
    	for (Polygon& p : faces) {
    		p.w_transform(m);
    	}
    }

	virtual const std::string to_string() const {
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

	virtual const ShapeType type() const {
		return ShapeType::Polyhedron;
	}

	Point medium;
	std::string name;
	std::vector<Polygon> faces;

protected:
	virtual const Point calculate_medium() {
		Vector m{0, 0, 0};
		for (Polygon& p : faces) {
			m = m + p.medium;
		}
		m = m / faces.size();
		return Point(m);
	}
};


#endif  // POLYHEDRON_H
