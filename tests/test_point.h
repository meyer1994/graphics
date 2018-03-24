#ifndef TEST_POINT_H
#define TEST_POINT_H

#include <cmath>
#include <iostream>
#include <assert.h>

#include <point.h>

#include "util.h"

namespace Test {

void point() {
    Point p0;
    assert(p0.size() == 0);
    std::cout << "[POINT]\t\tOK - default constructor" << std::endl;


    Point p1(std::vector<double>{1, 2, 3});
    assert(p1.size() == 3);
    assert(is_equal(p1[0], 1));
    assert(is_equal(p1[1], 2));
    assert(is_equal(p1[2], 3));
    std::cout << "[POINT]\t\tOK - explicit constructor" << std::endl;


    Point p2(1, 2);
    assert(p2.size() == 2);
    assert(is_equal(p2[0], 1));
    assert(is_equal(p2[1], 2));
    std::cout << "[POINT]\t\tOK - 2D constructor" << std::endl;


    Matrix scale_matrix = Transformation::scale(Vector{2, 2});
    Matrix expected_scale_matrix = {
        Vector{2, 0, 0},
        Vector{0, 2, 0},
        Vector{0, 0, 1}
    };
    compare_matrix(scale_matrix, expected_scale_matrix);
    std::cout << "[POINT]\t\tOK - Scale matrix" << std::endl;

    
    Point p3(5, 5);
    p3.scale(2);
    assert(is_equal(p3[0], 10));
    assert(is_equal(p3[1], 10));
    std::cout << "[POINT]\t\tOK - Scale" << std::endl;


    Matrix rotate_matrix = Transformation::rotate(90);
    double c = std::cos((-90 * _MATH_PI) / 180);
    double s = std::sin((-90 * _MATH_PI) / 180);
    Matrix expected_rotate_matrix = {
        Vector{c, -s, 0},
        Vector{s,  c, 0},
        Vector{0,  0, 1}
    };
    compare_matrix(rotate_matrix, expected_rotate_matrix);
    std::cout << "[POINT]\t\tOK - Rotate matrix" << std::endl;

    
    Point p4(5, 0);
    p4.rotate(90);
    assert(is_equal(p4[0], 0));
    assert(is_equal(p4[1], 5));
    std::cout << "[POINT]\t\tOK - Rotate" << std::endl;


    Matrix translate_matrix = Transformation::translate(Vector{10, 10});
    Matrix expected_translate_matrix = {
        Vector{ 1,  0, 0},
        Vector{ 0,  1, 0},
        Vector{10, 10, 1}
    };
    compare_matrix(translate_matrix, expected_translate_matrix);
    std::cout << "[POINT]\t\tOK - Translate matrix" << std::endl;


    Point p5(5, 0);
    p5.translate(Vector{1, 6});
    assert(is_equal(p5[0], 6));
    assert(is_equal(p5[1], 6));
    std::cout << "[POINT]\t\tOK - Translate" << std::endl;
}

}  // namespace Test

#endif  // TEST_POINT_H
