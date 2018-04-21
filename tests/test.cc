#include <iostream>
#include <assert.h>

#include <line.h>
#include <point.h>
#include <polyhedron.h>

void test_polyhedron() {
	// Pyramid base
	Line l0(Point(0, 0, 0), Point(100, 0, 0));
	Line l1(Point(100, 0, 0), Point(100, 0, 100));
	Line l2(Point(100, 0, 100), Point(0, 0, 0));

	// Pyramid top
	Line l3(Point(0, 0, 0), Point(50, 100, 50));
	Line l4(Point(100, 0, 0), Point(50, 100, 50));
	Line l5(Point(100, 0, 100), Point(50, 100, 50));

	std::vector<Line> lines{l0, l1, l2, l3, l4, l5};

	// Create 3D shape
	Polyhedron p = Polyhedron(lines);

	// Testing scale
	p.scale(2);
	for (int i = 0; i < lines.size(); i++) {
		lines[i].scale(2);
		assert(p[i] == lines[i]);
	}
	std::cout << "[Polyhedron]\t\tOK - Scale" << std::endl;


	// Test translate
	p.translate(10, 10, 10);
	for (int i = 0; i < lines.size(); i++) {
		lines[i].translate(10, 10, 10);
		assert(p[i] == lines[i]);
	}
	std::cout << "[Polyhedron]\t\tOK - Translate" << std::endl;
}

int main() {

	test_polyhedron();

    return 0;
}
