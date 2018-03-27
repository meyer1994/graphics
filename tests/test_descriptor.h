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


void to_file() {
	Polygon s(std::vector<Point>{
		Point(0, 0),
		Point(50, 0),
		Point(50, 50)
	});
	std::vector<Shape> shapes{s};
	ObjDescriptor obj(shapes);
	obj.write(test_file);
	std::cout << "File written" << std::endl;
}


}


#endif  // TEST_DESCRIPTOR_H
