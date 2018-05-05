#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>

#include "shape.h"
#include "point.h"
#include "vector.h"
#include "../transform.h"
#include "shape_complex.h"

class Polyhedron : public ShapeComplex {
public:
	Polyhedron() : ShapeComplex("polyhedron") {}

	Polyhedron(std::initializer_list<Shape*> d)
	: ShapeComplex(d, "polyhedron") {}

	Polyhedron(std::string name) : ShapeComplex(name) {}

	Polyhedron(std::vector<Shape*> faces, std::string name = "polyhedron")
	: ShapeComplex(faces, name) {
	  	if (faces.size() < 4) {
	  		throw std::invalid_argument("Polyhedron must have, at least, 4 faces");
	  	}
	}

	virtual ~Polyhedron() {}

	virtual const std::string to_string() const {
		if (faces.empty()) {
			return std::string("Polyhedron()");
		}

		std::string str = "Polyhedron(";
		for (int i = 0; i < faces.size() - 1; i++) {
			const Shape* p = faces[i];
			str += p->to_string() + ", ";
		}
		const Shape* last = faces.back();
		str += last->to_string() + ")";

		return str;
	}

	virtual const ShapeType type() const {
		return ShapeType::Polyhedron;
	}
};


#endif  // POLYHEDRON_H
