
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
	const Vector constr0 = Vector(3, 0);
	const Vector constr1 = Vector{0, 0, 0};
	const Vector constr2 = Vector(std::vector<double>{0, 0, 0});
	assert(constr0.size() == 3);
	assert(constr1.size() == 3);
	assert(constr2.size() == 3);
	assert(constr0 ==  constr1);
	assert(constr0 ==  constr2);
	assert(constr2 ==  constr1);
	std::cout << "[Vector]\tOK - Constructors" << std::endl;

	// Length
	const Vector length0{123, 353, 76, 5353, 34};
	const Vector length1{945, 128, -123, 123, 0};
	const Vector length2{0, 0, 0, 0, 0};
	assert(length0.length() == std::sqrt(28801279));
	assert(length1.length() == std::sqrt(939667));
	assert(length2.length() == 0);
	std::cout << "[Vector]\tOK - Length" << std::endl;

	// Angle
	const Vector angle0{281, 0, 123};
	const Vector angle1{0, 231, 0};
	const Vector angle2{7, 53, 121231};
	assert(is_equal(Vector::angle(angle0, angle1), 90));
	assert(is_equal(Vector::angle(angle1, angle2), 89.97495132337));
	assert(is_equal(Vector::angle(angle0, angle2), 66.35662085317));
	std::cout << "[Vector]\tOK - Angle" << std::endl;

	// Unit
	const Vector unit0{232, 897, 0, 0};
	const Vector unit1{232 / std::sqrt(858433), 897 / std::sqrt(858433), 0, 0};
	const Vector unit2{9, 5, 7, 1, 2, 3};
	const Vector unit3{9.0/13.0, 5.0/13.0, 7.0/13.0, 1.0/13.0, 2.0/13.0, 3.0/13.0};
	assert(compare(unit0.unit(), unit1));
	assert(compare(unit2.unit(), unit3));
	std::cout << "[Vector]\tOK - Unit vector" << std::endl;

	// Norm
	const Vector norm0{2323, 9890, 10238};
	const Vector norm1{0, 0, 0};
	const Vector norm2{36, 1930, 917273};
	assert(is_equal(norm0.norm(), 14423.0743255382));
	assert(is_equal(norm1.norm(), 0));
	assert(is_equal(norm2.norm(), 917275.0311247984));
	std::cout << "[Vector]\tOK - Norm" << std::endl;

	// Cross product
	const Vector cross0{12, 35, 2};
	const Vector cross1{90, 1, 3};
	const Vector cross2{1, 1, 1};
	assert(compare(Vector::cross(cross0, cross1), {103, 144, -3138}));
	assert(compare(Vector::cross(cross0, cross2), {33, -10, -23}));
	assert(compare(Vector::cross(cross1, cross2), {-2, -87, 89}));
	std::cout << "[Vector]\tOK - Cross product" << std::endl;

	// Operators tests

	// Equals
	const Vector equals0{1, 1, 1};
	const Vector equals1{1, 5, 2};
	const Vector equals2{1, -1, 2};
	assert(equals0 == equals0);
	assert(equals1 == equals1);
	assert(equals2 == equals2);
	std::cout << "[Vector]\tOK - Operator ==" << std::endl;

	// Not equals
	const Vector nequals0{1, 1, 0};
	const Vector nequals1{1, 5, 231};
	const Vector nequals2{1, -1, 999999};
	assert(nequals0 != nequals1);
	assert(nequals0 != nequals2);
	assert(nequals2 != nequals1);
	std::cout << "[Vector]\tOK - Operator !=" << std::endl;

	// Sum
	const Vector sum0{5, 5, 5};
	const Vector sum1{10, 10, 10};
	const Vector sum2{15, 15, 15};
	assert(sum0 + sum0 == sum1);
	assert(sum0 + sum1 == sum2);
	assert(sum0 + sum0 + sum0 == sum2);
	std::cout << "[Vector]\tOK - Operator +" << std::endl;

	// Minus
	const Vector minus0{-5, -5, -5};
	const Vector minus1{-15, -15, -15};
	const Vector minus2{10, 10, 10};
	assert(minus0 - minus2 == minus1);
	assert(minus0 - minus1 == minus2);
	std::cout << "[Vector]\tOK - Operator -" << std::endl;

	// Inverse
	const Vector inverse0{5, 5, 5};
	const Vector inverse1{-5, -5, -5};
	assert(inverse0 == -inverse1);
	assert(inverse1 == -inverse0);
	std::cout << "[Vector]\tOK - Operator - (inverse)" << std::endl;

	// Scalar
	const Vector scalar0{5, 10, 15};
	const Vector scalar1{10, 20, 30};
	const Vector scalar2{15, 30, 45};
	assert(compare(scalar0 * 2.0, scalar1));
	assert(compare(scalar1 * 0.5, scalar0));
	assert(compare(scalar1 * 1.5, scalar2));
	std::cout << "[Vector]\tOK - Operator * (double)" << std::endl;

	// Vector
	const Vector vector0{1, 2, 3, 4};
	const Vector vector1{5, 6, 7, 8};
	const Vector vector2{-231, -123, -312, -12};
	assert((vector0 * vector1) == 70);
	assert((vector0 * vector2) == -1461);
	assert((vector1 * vector2) == -4173);
	std::cout << "[Vector]\tOK - Operator * (Vector)" << std::endl;

	// Matrix
	const Vector matrix0{1, 2, 3};
	const Matrix matrix1{
		Vector{2, 3, 4},
		Vector{5, 6, 7},
		Vector{8, 9, 0}
	};
	const Vector matrix2{36, 42, 18};
	assert((matrix0 * matrix1) == matrix2);
	std::cout << "[Vector]\tOK - Operator * (Matrix)" << std::endl;
}

void test_matrix() {
	// Constructors
	const Matrix constr0{ Vector(3, 0), Vector(3, 0), Vector(3, 0) };
	const Matrix constr1(3, Vector(3, 0));
	const Matrix constr2(std::vector<Vector>{ Vector(3, 0), Vector(3, 0), Vector(3, 0) });
	assert(constr0.size() == 3);
	assert(constr1.size() == 3);
	assert(constr2.size() == 3);
	assert(constr0 == constr1);
	assert(constr0 == constr2);
	assert(constr2 == constr1);
	std::cout << "[Matrix]\tOK - Constructors" << std::endl;

	// Operators tests

	// Equals tested above (in constructors)
	std::cout << "[Matrix]\tOK - Operator ==" << std::endl;

	// Not equals
	const Matrix nequals0{
		Vector{0, 0, 1},
		Vector{0, 0, 1},
		Vector{0, 0, 1}
	};
	const Matrix nequals1{
		Vector{1, 0, 0},
		Vector{1, 0, 0},
		Vector{1, 0, 0}
	};
	const Matrix nequals2{
		Vector{0, 1, 0},
		Vector{0, 1, 0},
		Vector{0, 1, 0}
	};
	assert(nequals0 != nequals1);
	assert(nequals0 != nequals2);
	assert(nequals1 != nequals2);
	std::cout << "[Matrix]\tOK - Operator !=" << std::endl;


	// Scalar
	const Matrix scalar0{
		Vector{-5, -5, -5},
		Vector{-5, -5, -5},
		Vector{-5, -5, -5}
	};
	const Matrix scalar1{
		Vector{5, 5, 5},
		Vector{5, 5, 5},
		Vector{5, 5, 5}
	};
	const Matrix scalar2{
		Vector{10, 10, 10},
		Vector{10, 10, 10},
		Vector{10, 10, 10}
	};
	assert(scalar0 * -1 == scalar1);
	assert(scalar1 * -1 == scalar0);
	assert(scalar1 * 2 == scalar2);
	assert(scalar2 * 0.5 == scalar1);
	assert(scalar2 * -0.5 == scalar0);
	std::cout << "[Matrix]\tOK - Operator * (double)" << std::endl;

	// Vector
	const Matrix vector0{
		Vector{1, 2, 3},
		Vector{4, 5, 6},
		Vector{7, 8, 9}
	};
	const Vector vector1{16, 0, 3};
	const Vector vector2{-1, -2, 0};
	const Vector vector3{1, 1, 1};
	// Results
	const Vector vector4{25, 82, 139};
	const Vector vector5{-5, -14, -23};
	const Vector vector6{6, 15, 24};
	assert(compare(vector0 * vector1, vector4));
	assert(compare(vector0 * vector2, vector5));
	assert(compare(vector0 * vector3, vector6));
	std::cout << "[Matrix]\tOK - Operator * (Vector)" << std::endl;

	// Matrix
	const Matrix matrix0{
		Vector{2, 3, 4},
		Vector{5, 6, 7},
		Vector{8, 9, 0}
	};
	const Matrix matrix1{
		Vector{1, 2, 3},
		Vector{2, 5, 8},
		Vector{3, 1, 2}
	};
	const Matrix matrix2{
		Vector{1, 0, 0},
		Vector{0, 1, 0},
		Vector{0, 0, 1}
	};
	// Result of matrix0 * matrix1
	const Matrix matrix3{
		Vector{20, 23, 38},
		Vector{38, 47, 77},
		Vector{26, 61, 96},
	};
	assert(compare(matrix0 * matrix1, matrix3));
	assert(compare(matrix0 * matrix2, matrix0));
	assert(compare(matrix1 * matrix2, matrix1));
	assert(compare(matrix3 * matrix2, matrix3));
	std::cout << "[Matrix]\tOK - Operator * (Matrix)" << std::endl;
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

	// Distance test
	Point d0(22, 38, 85);
	Point d1(71, 3, 29);
	double distance = 7 * std::sqrt(138);
	assert(is_equal(distance, d0.distance(d1)));
	std::cout << "[Point]\t\tOK - Distance" << std::endl;
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

	// Rotation arbitrary axis test
	Line r0(Point(0, 0, 5), Point(5, 0, 5));
	Line r1(Point(0, 0, 5), Point(0, 5, 5));
	r0.rotate(90, {0, 0, 1});
	assert(compare(r0, r1));
	std::cout << "[Line]\t\tOK - Rotate axis" << std::endl;

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
	Point med(200.0, 100.0, 200.0);
	assert(compare(m.medium, med * (1.0 / 3.0)));
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

	// Rotation arbitrary axis test
	Polygon r0({
		Point(0, 0, 0),
		Point(0, 0, 100),
		Point(100, 0, 100)
	});
	Polygon r1({
		Point(0, 0, 0),
		Point(0, 100, 0),
		Point(100, 100, 0)
	});
	r0.rotate(-90, {1, 0, 0});
	assert(compare(r0, r1));
	std::cout << "[Polygon]\tOK - Rotate axis" << std::endl;

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
