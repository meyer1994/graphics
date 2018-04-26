
#include <string>
#include <iostream>
#include <assert.h>

// Shapes
#include <dot.h>
#include <line.h>
#include <point.h>
#include <polygon.h>

// Math
#include <vector.h>
#include <transform.h>

#include "util.h"

void test_vector() {
	// Constructors tests
	Vector c0(3, 0);
	Vector c1{0, 0, 0};
	Vector c2(std::vector<double>{0, 0, 0});
	assert(compare(c0, c1));
	assert(compare(c0, c2));
	assert(compare(c1, c2));
	std::cout << "[Vector]\tOK - Constructors" << std::endl;

	// Length
	Vector l{4, 65, 1};
	double rl = std::sqrt(4242);
	assert(is_equal(rl, l.length()));
	std::cout << "[Vector]\tOK - Length" << std::endl;

	// Angle
	Vector a0{19, 2, 64};
	Vector a1{3, 6, 101};
	double angle = 14.913282135635228;
	assert(is_equal(angle, a0.angle(a1)));
	std::cout << "[Vector]\tOK - Angle" << std::endl;

	// Operators tests

	// Equals
	bool e0 = Vector{1, 2, 3} == Vector{1, 2, 3};
	bool e1 = Vector{1, 2, 3} == Vector{3, 2, 1};
	assert(e0);
	assert(!e1);
	std::cout << "[Vector]\tOK - Operator==" << std::endl;

	// Scalar
	Vector o0{0, 1, 2, 3};
	o0 = o0 * 3;
	Vector r0{0, 3, 6, 9};
	assert(compare(o0, r0));
	std::cout << "[Vector]\tOK - Operator* (double)" << std::endl;

	// Vector
	Vector o1{1, 2, 3, 4};
	Vector t1{5, 6, 7, 8};
	double res = 5 + 2*6 + 3*7 + 4*8;
	assert(is_equal(res, o1 * t1));
	std::cout << "[Vector]\tOK - Operator* (Vector)" << std::endl;

	// Matrix
	Vector o2{1, 2, 3};
	Matrix m2{
		Vector{2, 3, 4},
		Vector{5, 6, 7},
		Vector{8, 9, 0}
	};
	Vector r2{36, 42, 18};
	assert(compare(r2, o2*m2));
	std::cout << "[Vector]\tOK - Operator* (Matrix)" << std::endl;
}

void test_matrix() {
	// Constructors tests
	Matrix m0(3, Vector(3, 0));
	Matrix m1{
		Vector(3, 0),
		Vector(3, 0),
		Vector(3, 0)
	};
	Matrix m2(std::vector<Vector>(3, Vector(3, 0)));
	assert(compare(m0, m1));
	assert(compare(m0, m2));
	assert(compare(m1, m2));
	std::cout << "[Matrix]\tOK - Constructors" << std::endl;

	// Operators tests

	// Equals
	bool e0 = Matrix(1, Vector(2, 0)) == Matrix(1, Vector(2, 0));
	bool e1 = Matrix(1, Vector(2, 0)) == Matrix(1, Vector(2, 1));
	assert(e0);
	assert(!e1);
	std::cout << "[Matrix]\tOK - Operator==" << std::endl;

	// Scalar
	Matrix o0{
		Vector(3, 1),
		Vector(3, 2),
		Vector(3, 3)
	};
	o0 = o0 * 3;
	Matrix r0{
		Vector(3, 3),
		Vector(3, 6),
		Vector(3, 9)
	};
	assert(compare(r0, o0));
	std::cout << "[Matrix]\tOK - Operator* (double)" << std::endl;

	// Vector
	Matrix o1{
		{2, 3, 4},
		{5, 6, 7},
		{8, 9, 0}
	};
	Vector t1{1, 2, 3};
	Vector res1{20, 38, 26};
	assert(compare(res1, o1 * t1));
	std::cout << "[Matrix]\tOK - Operator* (Vector)" << std::endl;

	// Matrix
	Matrix o2{
		{2, 3, 4},
		{5, 6, 7},
		{8, 9, 0}
	};
	Matrix t2{
		{1, 2, 3},
		{2, 5, 8},
		{3, 1, 2}
	};
	Matrix res0{
		{20, 23, 38},
		{38, 47, 77},
		{26, 61, 96}
	};
	assert(compare(res0, o2 * t2));
	std::cout << "[Matrix]\tOK - Operator* (Matrix)" << std::endl;
}

void test_point() {
	// Rotation test
	Point a(5, 5, 0);
	const Matrix rx = Transform::rotatex(90);
	a.transform(rx);
	assert(compare(a, Point(5, 0, 5)));

	const Matrix ry = Transform::rotatey(90);
	a.transform(ry);
	assert(compare(a, Point(5, 0, -5)));

	const Matrix rz = Transform::rotatez(90);
	a.transform(rz);
	assert(compare(a, Point(0, 5, -5)));
	std::cout << "[Point]\t\tOK - Rotate" << std::endl;

	// Scale test
	Point b(5, 5, 5);
	const Matrix s = Transform::scale(2, 2, 2);
	b.transform(s);
	assert(compare(b, Point(10, 10, 10)));
	std::cout << "[Point]\t\tOK - Scale" << std::endl;

	// Translate test
	Point c(5, 5, 5);
	const Matrix t = Transform::translate(10, -5, 1);
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
	std::cout << "==================" << std::endl;
	std::cout << "= STARTING TESTS =" << std::endl;
	std::cout << "==================" << std::endl;
	std::cout << std::endl;

	test_vector();
	test_matrix();

	test_point();
	test_line();
	test_dot();
	test_polygon();

	std::cout << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << "= ALL TESTS PASSED =" << std::endl;
	std::cout << "====================" << std::endl;

    return 0;
}
