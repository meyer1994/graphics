#ifndef OBJ_DESCRIPTOR_H
#define OBJ_DESCRIPTOR_H

#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

#include "shape.h"

class ObjDescriptor {
public:
	explicit ObjDescriptor(std::vector<Shape>& s) : shapes(s) {}

	~ObjDescriptor() {}

	void write(std::string fname) {

		std::ofstream file;
		file.open(fname);
		int line_counter = 1;

		std::string points;
		std::string objects;

		for (Shape& s : shapes) {
			points += get_points(s);

			objects += "o meu_objeto" + std::to_string(line_counter);
			objects += "\n";

			objects += get_type(s);
			for (int i = 0; i < s.size(); i++) {
				objects += " " + std::to_string(line_counter + i);
			}
			line_counter += s.size();
			objects += "\n";
		}

		file << points;
		file << objects;

		file.close();
	}

	std::vector<Shape>& shapes;

protected:
	std::string get_points(Shape& shape) {
		std::string str;
		for (Point& p : shape.points_real) {
			str += "v";
			for (double d : p) {
				str += " " + std::to_string(d);
			}
			str += "\n";
		}
		return str;
	}

	std::string get_type(Shape& shape) {
		int size = shape.size();
		if (size == 1) {
			return "p";
		}

		return "l";
	}
};

#endif  // OBJ_DESCRIPTOR_H
