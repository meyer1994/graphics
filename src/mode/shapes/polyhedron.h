#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <string>
#include <vector>

#include "line.h"
#include "point.h"
#include "shape3d.h"

class Polyhedron : public Shape3D {
public:
	Polyhedron() : Shape3D("polyhedron") {}

	explicit Polyhedron(std::string name) : Shape3D(name) {}

	Polyhedron(std::vector<Line> lines) : Shape3D(lines, "polyhedron") {}

	virtual ~Polyhedron() {}

	virtual const std::string to_string() const override {
		if (lines.empty()) {
			return std::string("Polyhedron()");
		}

		std::string str = "Polyhedron(";

		for (int i = 0; i < size() - 1; i++) {
			const Line& l = lines[i];
			str += l.to_string() + ", ";
		}

		const Line& last = lines.back();
		str += last.to_string() + ")";

		return str;
	}

	virtual const Type3D type() const override {
		return Type3D::Polyhedron;
	}
};

#endif  // POLYHEDRON_H
