#ifndef OBJ_DESCRIPTOR_H
#define OBJ_DESCRIPTOR_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "dot.h"
#include "line.h"
#include "shape.h"
#include "polygon.h"

namespace Mode {

/**
 * @brief Obj descriptor class.
 * 
 * @details This class is used to write and read files in the form of .obj. The
 * file stored in this pattern can be loaded into the software for use.
 * @return [description]
 */
class ObjDescriptor {
public:
	/**
	 * @brief Explicit constructor.
	 * 
	 * @param s The vector where to append the shapes to, or get the info to
	 * write them to the disk.
	 */
	explicit ObjDescriptor(std::vector<Shape*>& s) : shapes(s) {}

	virtual ~ObjDescriptor() {}

	/**
	 * @brief Write the shapes to disk.
	 * 
	 * @details The shapes referenced in the vector passed in the contructor
	 * will be written in the disk.
	 * 
	 * @param fname File name to write to.
	 */
	void write(std::string fname) {
		std::ofstream file(fname);
		int line_counter = 1;

		std::string points;
		std::string objects;

		for (Shape* s : shapes) {
			points += points_to_obj(*s);

			objects += "o meu_objeto" + std::to_string(line_counter);
			objects += "\n";

			objects += get_type(*s);
			for (int i = 0; i < s->size(); i++) {
				objects += " " + std::to_string(line_counter + i);
			}
			line_counter += s->size();
			objects += "\n";
		}

		file << points;
		file << objects;

		file.close();
	}

	/**
	 * @brief Reads .obj from file.
	 * 
	 * @details Reads the objects from the file and appends them to the shapes
	 * vector.
	 * 
	 * @param fname File name to read from.
	 */
	void read(std::string fname) {
		std::ifstream file(fname);
		std::stringstream buffer;
		buffer << file.rdbuf();

		std::string contents = buffer.str();
		std::vector<Point> points;

		int index = 0;
		while (index < contents.size()) {
			char c = contents[index];

			// Points
			if (c == 'v') {
				points.push_back(get_point(contents, index));

			// Objects
			} else if (c == 'o') {
				shapes.push_back(get_shape(contents, points, index));
			}
		}
	}

	std::vector<Shape*>& shapes;

protected:
	std::string points_to_obj(const Shape& shape) {
		std::string str;
		for (const Point& p : shape.real) {
			str += "v";
			for (double d : p) {
				str += " " + std::to_string(d);
			}
			str += "\n";
		}
		return str;
	}

	std::string get_type(const Shape& shape) {
		int size = shape.size();
		if (size == 1) {
			return "p";
		}

		return "l";
	}

	Point get_point(const std::string& line, int& index) {
		// Goes to first char of values
		index += 2;

		std::vector<double> values;
		std::string buffer;

		while (index < line.size()) {
			char c = line[index];

			// End of this point
			if (c == '\n') {
				break;
			}

			// End of value
			if (c == ' ') {
				values.push_back(std::stod(buffer));
				buffer.clear();
				index++;
				continue;
			}

			buffer += c;

			// Next char
			index++;
		}

		// Append last value and return point
		index++;
		values.push_back(std::stod(buffer));
		return Point(values);
	}

	Shape* get_shape(const std::string& contents,
					const std::vector<Point>& p,
					int& index) {
		// Goes to first char of object name
		index += 1;

		// Gets name
		std::string name;
		while (index < contents.size()) {
			char c = contents[index];

			// End of name
			if (c == '\n') {
				break;
			}

			name += c;
			index++;
		}

		// Next line
		index += 3;

		std::vector<Point> points;
		std::string buffer;
		while (index < contents.size()) {
			char c = contents[index];

			// End of point list
			if (c == '\n') {
				break;
			}

			if (c == ' ') {
				int point_i = std::stoi(buffer);
				buffer.clear();
				points.push_back(p[point_i - 1]);
				index++;
				continue;
			}

			buffer += c;

			index++;
		}

		index++;
		int point_i = std::stoi(buffer);
		points.push_back(p[point_i - 1]);

		int size = points.size();
		switch (size) {
			case 1:
			{
				return new Dot(points[0], "dot");
			}
			case 2:
			{	
				Point a = points[0];
				Point b = points[1];
				return new Line(a, b);
			}
			default:
			{
				return new Polygon(points);
			}
		}
	}
};

}  // namespace Mode

#endif  // OBJ_DESCRIPTOR_H
