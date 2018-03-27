#ifndef TEST_DESCRIPTOR_H
#define TEST_DESCRIPTOR_H

#include <iostream>
#include <vector>
#include <string>

#include <shape.h>
#include <polygon.h>
#include <objdescriptor.h>

const std::string test_file = "test.obj";

namespace Test {


void write() {
	Polygon s0(std::vector<Point>{
		Point(0, 0),
		Point(50, 0),
		Point(50, 50)
	});
	Polygon s1(std::vector<Point>{
		Point(25, 25),
		Point(10, 10)
	});
	std::vector<Shape> shapes{s0, s1};
	ObjDescriptor obj(shapes);
	obj.write(test_file);
	std::cout << "File written" << std::endl;
}

void read() {
	std::vector<Shape> s;
	ObjDescriptor obj(s);
	obj.read(test_file);

	for (Shape& sh : s)
		std::cout << sh.to_string() << std::endl;
}


}


#endif  // TEST_DESCRIPTOR_H
