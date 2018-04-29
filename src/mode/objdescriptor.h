#ifndef OBJ_DESCRIPTOR_H
#define OBJ_DESCRIPTOR_H

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "shapes/dot.h"
#include "shapes/line.h"
#include "shapes/shape.h"
#include "shapes/polygon.h"
#include "shapes/polyhedron.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace Mode {


class ObjDescriptor {
public:
	/**
	 * @brief Explicit constructor.
	 * 
	 * @param s The vector where to append the shapes to, or get the info to
	 * write them to the disk.
	 */
	explicit ObjDescriptor(std::vector<BaseShape*>& s) : shapes(s) {}

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
		// std::ofstream file(fname);
		// int line_counter = 1;

		// std::string points;
		// std::string objects;

		// for (BaseShape* s : shapes) {
		// 	// Get object points
		// 	points += points_to_obj(s);

		// 	// Get name
		// 	objects += "o " + s->name;
		// 	objects += "\n";

		// 	// Get type
		// 	objects += get_type(s);

		// 	// Polyhedron
		// 	if (s->type() == ShapeType::Polyhedron) {
		// 		const Polyhedron* poly = dynamic_cast<const Polyhedron*>(s);
		// 		for (const Polygon& p : s->faces) {
		// 			for (const Point& f : p.real) {
		// 				objects += " " + std::to_string(line_counter + i);
		// 			}
				
		// 		}			

		// 	// Regular shape
		// 	} else {
				
		// 	}

		// 	line_counter += s->size();
		// 	objects += "\n";
		// }

		// file << points;
		// file << objects;

		// file.close();
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
		std::string inputfile = fname;
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes_tiny;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes_tiny, &materials, &err, inputfile.c_str());

		// `err` may contain warning message.
		if (!err.empty()) { 
			std::cerr << err << std::endl;
		}

		if (!ret) {
			return;
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes_tiny.size(); s++) {
			const std::string shape_name = shapes_tiny[s].name;
			std::vector<Polygon> polys;

			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes_tiny[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes_tiny[s].mesh.num_face_vertices[f];

				std::vector<Point> points;

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes_tiny[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
					tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
					tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];

					points.push_back(Point{vx, vy, vz});
				}

				polys.push_back(Polygon(points));
				index_offset += fv;
			}
			
			// Add to display file
			shapes.push_back(new Polyhedron(polys, shape_name));
		}
	}


	std::vector<BaseShape*>& shapes;

protected:

	// const std::string get_points() {
	// 	int line = 1;
	// 	std::string points;
	// 	for (const BaseShape* base : shapes) {
	// 		points += points_to_obj(base);
	// 	}

	// 	return points;
	// }

	// const std::string points_to_obj(const BaseShape* s) {
	// 	std::string str;

	// 	// Regular shapes
	// 	const Shape* shape = dynamic_cast<const Shape*>(s);
	// 	if (shape != nullptr) {
	// 		for (const Point& p : shape->real) {
	// 			str += "v";
	// 			for (double d : p) {
	// 				str += " " + std::to_string(d);
	// 			}
	// 			str += "\n";
	// 		}
	// 		return str;
	// 	}

	// 	// Polyhedron
	// 	const Polyhedron* poly = dynamic_cast<const Polyhedron*>(s);
	// 	if (poly != nullptr) {
	// 		for (const Shape& sh : poly->faces) {
	// 			str += points_to_obj(&sh);
	// 		}
	// 		return str;
	// 	}

	// 	return "";
	// }

	// const std::string get_type(const BaseShape& shape) {
	// 	const ShapeType type == shape->type();
	// 	if (type == ShapeType::Dot) {
	// 		return "p";
	// 	}
	// 	return "l";
	// }

	// Point get_point(const std::string& line, int& index) {
	// 	// Goes to first char of values
	// 	index += 2;

	// 	std::vector<double> values;
	// 	std::string buffer;

	// 	while (index < line.size()) {
	// 		char c = line[index];

	// 		// End of this point
	// 		if (c == '\n') {
	// 			break;
	// 		}

	// 		// End of value
	// 		if (c == ' ') {
	// 			values.push_back(std::stod(buffer));
	// 			buffer.clear();
	// 			index++;
	// 			continue;
	// 		}

	// 		buffer += c;

	// 		// Next char
	// 		index++;
	// 	}

	// 	// Append last value and return point
	// 	index++;
	// 	values.push_back(std::stod(buffer));
	// 	return Point(values);
	// }

	// Shape* get_shape(const std::string& contents, const std::vector<Point>& p, int& index) {
	// 	// Goes to first char of object name
	// 	index += 1;

	// 	// Gets name
	// 	std::string name;
	// 	while (index < contents.size()) {
	// 		char c = contents[index];

	// 		// End of name
	// 		if (c == '\n') {
	// 			break;
	// 		}

	// 		name += c;
	// 		index++;
	// 	}

	// 	// Next line
	// 	index += 3;

	// 	std::vector<Point> points;
	// 	std::string buffer;
	// 	while (index < contents.size()) {
	// 		char c = contents[index];

	// 		// End of point list
	// 		if (c == '\n') {
	// 			break;
	// 		}

	// 		if (c == ' ') {
	// 			int point_i = std::stoi(buffer);
	// 			buffer.clear();
	// 			points.push_back(p[point_i - 1]);
	// 			index++;
	// 			continue;
	// 		}

	// 		buffer += c;

	// 		index++;
	// 	}

	// 	index++;
	// 	int point_i = std::stoi(buffer);
	// 	points.push_back(p[point_i - 1]);

	// 	int size = points.size();
	// 	switch (size) {
	// 		case 1:
	// 		{
	// 			return new Dot(points[0], "dot");
	// 		}
	// 		case 2:
	// 		{	
	// 			Point a = points[0];
	// 			Point b = points[1];
	// 			return new Line(a, b);
	// 		}
	// 		default:
	// 		{
	// 			return new Polygon(points);
	// 		}
	// 	}
	// }
};

}  // namespace Mode

#endif  // OBJ_DESCRIPTOR_H
