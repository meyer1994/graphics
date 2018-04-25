#include <iostream>
#include <assert.h>

#include <dot.h>
#include <line.h>
#include <point.h>
#include <polygon.h>

#include "util.h"


void test_point() {
	// Rotation test
	Point a(5, 5, 0);
	const Matrix rx = Transformation::rotatex(90);
	a.transform(rx);
	assert(compare(a, Point(5, 0, 5)));

	const Matrix ry = Transformation::rotatey(90);
	a.transform(ry);
	assert(compare(a, Point(5, 0, -5)));

	const Matrix rz = Transformation::rotatez(90);
	a.transform(rz);
	assert(compare(a, Point(0, 5, -5)));
	std::cout << "[Point]\t\tOK - Rotate" << std::endl;

	// Scale test
	Point b(5, 5, 5);
	const Matrix s = Transformation::scale(2, 2, 2);
	b.transform(s);
	assert(compare(b, Point(10, 10, 10)));
	std::cout << "[Point]\t\tOK - Scale" << std::endl;

	// Translate test
	Point c(5, 5, 5);
	const Matrix t = Transformation::translate(10, -5, 1);
	c.transform(t);
	assert(compare(c, Point(15, 0, 6)));
	std::cout << "[Point]\t\tOK - Translate" << std::endl;
}

void test_dot() {
	// Medium test
	Dot m(50, 50, 50);
	assert(compare(m, Dot(50, 50, 50)));
	std::cout << "[Dot]\t\tOK - Medium" << std::endl;

	// Rotation test
	Dot a(5, 5, 5);
	a.rotate(-90, -90, 0);
	assert(compare(a, Dot(5, 5, 5)));
	std::cout << "[Dot]\t\tOK - Rotate" << std::endl;

	// Scale test
	Dot b(5, 5, 5);
	b.scale(2);
	assert(compare(b, Dot(10, 10, 10)));
	std::cout << "[Dot]\t\tOK - Scale" << std::endl;

	// Translate test
	Dot c(5, 5, 5);
	c.translate(10, -5, 11);
	assert(compare(c, Dot(15, 0, 16)));
	std::cout << "[Dot]\t\tOK - Translate" << std::endl;
}

void test_line() {
	// Medium test
	Line m(Point(50, 25), Point(10, 32));
	assert(compare(m.medium, Point(30, 28.5)));
	std::cout << "[Line]\t\tOK - Medium" << std::endl;

	// Rotation test
	Line l0(Point(0, 0, 0), Point(10, 0, 0));
	Line la(Point(0, 0, 0), Point(0, 0, -10));
	l0.rotate(0, 90, 0);
	assert(compare(l0, la));
	std::cout << "[Line]\t\tOK - Rotate" << std::endl;

	// Scale test
	Line l1(Point(20, 10, 0), Point(15, 10, 0));
	Line lb(Point(40, 20, 0), Point(30, 20, 0));
	l1.scale(2);
	assert(compare(l1, lb));
	std::cout << "[Line]\t\tOK - Scale" << std::endl;

	// Translate test
	Line l2(Point(11, 25, 0), Point(13, 4, 0));
	Line lc(Point(22, 50, 0), Point(24, 29, 0));
	l2.translate(11, 25, 0);
	assert(compare(l2, lc));
	std::cout << "[Line]\t\tOK - Translate" << std::endl;
}

void test_polygon() {
	std::vector<Point> points{
		Point(0, 0, 0),
		Point(100, 0, 100),
		Point(100, 100, 100)
	};

	// Medium test
	Polygon m(points);
	assert(compare(m.medium, Point(200.0 / 3.0, 100.0 / 3.0, 200.0 / 3.0)));
	std::cout << "[Polygon]\tOK - Medium" << std::endl;

	// Rotate test
	Polygon r(points);
	r.rotate(0, -90, -180);
	assert(compare(r, Polygon({
		Point(0, 0, 0),
		Point(100, 0, 100),
		Point(100, -100, 100)
	})));
	std::cout << "[Polygon]\tOK - Rotate" << std::endl;

	// Scale test
	Polygon s(points);
	s.scale(2);
	assert(compare(s, Polygon({
		Point(0, 0, 0),
		Point(200, 0, 200),
		Point(200, 200, 200)
	})));
	std::cout << "[Polygon]\tOK - Scale" << std::endl;

	// Translate test
	Polygon t(points);
	t.translate(10, 11, 13.2);
	assert(compare(t, Polygon({
		Point(10, 11, 13.2),
		Point(110, 11, 113.2),
		Point(110, 111, 113.2)
	})));
	std::cout << "[Polygon]\tOK - Translate" << std::endl;
}


int main() {
	test_point();
	test_line();
	test_dot();
	test_polygon();

    return 0;
}
