
#include <string>
#include <iostream>
#include <assert.h>

// Shapes
#include <dot.h>
#include <line.h>
#include <point.h>
#include <polygon.h>
#include <polyhedron.h>

// Math
#include <vector.h>
#include <transform.h>

#include "util.h"

void test_vector() {
	// Constructors tests
	const Vector constr0(3, 0);
	const Vector constr1{0, 0, 0};
	const Vector constr2(std::vector<double>{0, 0, 0});
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
	assert(compare(Vector::angle(angle0, angle1), 90));
	assert(compare(Vector::angle(angle1, angle2), 89.97495132337));
	assert(compare(Vector::angle(angle0, angle2), 66.35662085317));
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
	assert(compare(norm0.norm(), 14423.0743255382));
	assert(compare(norm1.norm(), 0));
	assert(compare(norm2.norm(), 917275.0311247984));
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

	// Sum
	const Matrix plus0{
		{5, 5, 5},
		{5, 5, 5},
		{5, 5, 5}
	};
	const Matrix plus1{
		{10, 10, 10},
		{10, 10, 10},
		{10, 10, 10}
	};
	const Matrix plus2{
		{15, 15, 15},
		{15, 15, 15},
		{15, 15, 15}
	};
	assert(plus0 + plus1 == plus2);
	assert(plus1 + plus0 == plus2);
	assert(plus0 + plus0 + plus0 == plus2);
	assert(plus0 + plus0 == plus1);
	std::cout << "[Matrix]\tOK - Operator +" << std::endl;

	// Minus
	// Using the matrices from above test
	assert(plus2 - plus1 == plus0);
	assert(plus1 - plus0 == plus0);
	assert(plus2 - plus0 - plus0 == plus0);
	assert(plus2 - plus0 == plus1);
	std::cout << "[Matrix]\tOK - Operator -" << std::endl;

	// Inverse
	// Again, using the matrices declared in the operator + test
	const Matrix inver0{
		{-5, -5, -5},
		{-5, -5, -5},
		{-5, -5, -5}
	};
	const Matrix inver1{
		{-10, -10, -10},
		{-10, -10, -10},
		{-10, -10, -10}
	};
	const Matrix inver2{
		{-15, -15, -15},
		{-15, -15, -15},
		{-15, -15, -15}
	};
	assert(inver0 == -plus0);
	assert(-inver0 == plus0);
	assert(inver1 == -plus1);
	assert(-inver1 == plus1);
	assert(inver2 == -plus2);
	assert(-inver2 == plus2);
	std::cout << "[Matrix]\tOK - Operator - (inverse)" << std::endl;


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

	const Matrix id0 = Matrix::identity(1);
	const Matrix id1 = Matrix::identity(3);
	const Matrix id2 = Matrix::identity(5);
	assert(id0[0][0] == 1);
	for (int i = 0; i < id1.size(); i++) {
		assert(id1[i][i] == 1);
	}
	for (int i = 0; i < id2.size(); i++) {
		assert(id2[i][i] == 1);
	}
	std::cout << "[Matrix]\tOK - Identity" << std::endl;
}

void test_point() {
	// Constructors
	const Point constr0{1, 2, 3};
	const Point constr1(1, 2, 3);
	const Point constr2({1, 2, 3});
	const Point constr3;
	assert(constr0.size() == 3);
	assert(constr1.size() == 3);
	assert(constr2.size() == 3);
	assert(constr3.size() == 3);
	std::cout << "[Point]\t\tOK - Constructors" << std::endl;

	// Transform
	Point trans0{10, 0, 0};
	const Matrix trans1 = Transform::scale(2, 2, 2);
	const Matrix trans2 = Transform::rotatey(90);
	const Matrix trans3 = Transform::translate(0, 0, 20);
	trans0.transform(trans1);
	assert(compare(trans0, Point(20, 0, 0)));
	trans0.transform(trans2);
	assert(compare(trans0, Point(0, 0, -20)));
	trans0.transform(trans3);
	assert(compare(trans0, Point(0, 0, 0)));
	std::cout << "[Point]\t\tOK - Transform" << std::endl;

	// Distance
	const Point dist0{12, -322, 11};
	const Point dist1{1, 65, 0};
	const Point dist2{1, 1, 0};
	// Result
	const double dist01_res = Point::distance(dist1, dist0);
	assert(compare(dist0.distance(dist1), std::sqrt(150011)));
	assert(compare(dist1.distance(dist0), std::sqrt(150011)));
	assert(compare(dist01_res, std::sqrt(150011)));
	assert(compare(dist2.distance(dist1), 64));
	std::cout << "[Point]\t\tOK - Distance" << std::endl;
}

void test_dot() {
	// Constructors
	const Dot constr0;
	const Dot constr1 = Dot(1, 2, 3);
	const Dot constr2 = Dot(Point(1, 2, 3));
	assert(constr0.real.size() == 1);
	assert(constr1.real.size() == 1);
	assert(constr2.real.size() == 1);
	std::cout << "[Dot]\t\tOK - Constructors" << std::endl;

	// Medium test
	const Dot med0(50, 50, 50);
	const Dot med1(100, 100, 100);
	const Dot med2(-10, -10, -10);
	assert(compare(med0.medium, Point(50, 50, 50)));
	assert(compare(med1.medium, Point(100, 100, 100)));
	assert(compare(med2.medium, Point(-10, -10, -10)));
	std::cout << "[Dot]\t\tOK - Medium" << std::endl;

	// Rotation test
	Dot rot0(5, 5, 5);
	Dot rot1(10, 5, 0);
	Dot rot2(-1, -1, -1);
	rot0.rotate(90, 0, 0);
	rot1.rotate(0, -90, 0);
	rot2.rotate(0, 0, 180);
	assert(compare(rot0, Dot(5, -5, 5)));
	assert(compare(rot1, Dot(0, 5, 10)));
	assert(compare(rot2, Dot(1, 1, -1)));
	std::cout << "[Dot]\t\tOK - Rotate" << std::endl;

	// Scale test
	Dot scale0(1, 2, 3);
	Dot scale1(5, 5, 5);
	Dot scale2(-1, -1, -1);
	scale0.scale(3);
	scale1.scale(-2);
	scale2.scale(0.5);
	assert(compare(scale0, Dot(3, 6, 9)));
	assert(compare(scale1, Dot(-10, -10, -10)));
	assert(compare(scale2, Dot(-0.5, -0.5, -0.5)));
	std::cout << "[Dot]\t\tOK - Scale" << std::endl;

	// Inflate
	Dot infl0(0, 5, 5);
	Dot infl1(5, 0, 5);
	Dot infl2(5, 5, 0);
	infl0.inflate(1);
	infl1.inflate(2);
	infl2.inflate(3);
	assert(infl0 == Dot(0, 5, 5));
	assert(infl1 == Dot(5, 0, 5));
	assert(infl2 == Dot(5, 5, 0));
	std::cout << "[Dot]\t\tOK - Inflate" << std::endl;

	// Translate test
	Dot trans0(5, 5, 5);
	Dot trans1(-5, 0, 1);
	Dot trans2(0, 0, 0);
	trans0.translate(5, 5, -5);
	trans1.translate(1, 2, -0.5);
	trans2.translate(-3, 1, 100);
	assert(compare(trans0, Dot(10, 10, 0)));
	assert(compare(trans1, Dot(-4, 2, 0.5)));
	assert(compare(trans2, Dot(-3, 1, 100)));
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

void test_polyhedron() {
	// Faces to be used
	// It is, basically, a pyramid
	const std::vector<Polygon> faces{
		// Base
		Polygon{
			Point(0, 0, 0),
			Point(100, 0, 0),
			Point(0, 0, 100)
		},
		// Sides
		Polygon{
			Point(0, 0, 0),
			Point(100, 0, 0),
			Point(0, 100, 0),
		},
		Polygon{
			Point(0, 0, 0),
			Point(0, 0, 100),
			Point(0, 100, 0)
		},
		Polygon{
			Point(100, 0, 0),
			Point(0, 0, 100),
			Point(0, 100, 0)
		}
	};

	// Constructors
	const Polyhedron constr0{ faces[0], faces[1], faces[2], faces[3] };
	const Polyhedron constr1(faces);
	assert(constr0.faces.size() == 4);
	assert(constr1.faces.size() == 4);
	assert(constr0.medium != Vector(3, 0));
	std::cout << "[Polyhedron]\tOK - Constructors" << std::endl;


	std::cout << "[Polyhedron]\tOK - Constructors" << std::endl;
}

int main() {

	std::cout << "==================" << std::endl;
	std::cout << "= STARTING TESTS =" << std::endl;
	std::cout << "==================" << std::endl;
	std::cout << std::endl;

	test_vector();
	test_matrix();

	test_point();

	test_dot();
	test_line();
	test_polygon();
	test_polyhedron();

	std::cout << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << "= ALL TESTS PASSED =" << std::endl;
	std::cout << "====================" << std::endl;

    return 0;
}
