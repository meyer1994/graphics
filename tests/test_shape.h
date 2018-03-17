#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

#include <iostream>
#include <assert.h>

#include <shape.h>

#include "util.h"

namespace Test {

void shape() {

    Shape s0;
    assert(s0.size() == 0);
    assert(s0.points_real.size() == 0);
    assert(s0.points_window.size() == 0);
    std::cout << "[SHAPE]\t\tOK - Default constructor" << std::endl;


    Shape s1(std::vector<Point>{
        Point(1, 1),
        Point(2, 3),
        Point(3, 1)
    });
    assert(s1.size() == 3);
    assert(s1.points_real.size() == 3);
    std::cout << "[SHAPE]\t\tOK - Explicit constructor" << std::endl;


    Shape s2(std::vector<Point>{
        Point(1, 1),
        Point(2, 3),
        Point(3, 1)
    });
    s2.scale(2);
    assert(s2.points_real[0] == Point(2, 2));
    assert(s2.points_real[1] == Point(4, 6));
    assert(s2.points_real[2] == Point(6, 2));
    std::cout << "[SHAPE]\t\tOK - Scale matrix" << std::endl;


    Shape s3(std::vector<Point>{
        Point(1, 1),
        Point(1, 2),
        Point(2, 2),
        Point(2, 1)
    });
    s3.rotate(90);
    assert(is_equal(s3.points_real[0][0], -1));
    assert(is_equal(s3.points_real[0][1],  1));
    assert(is_equal(s3.points_real[1][0], -2));
    assert(is_equal(s3.points_real[1][1],  1));
    assert(is_equal(s3.points_real[2][0], -2));
    assert(is_equal(s3.points_real[2][1],  2));
    assert(is_equal(s3.points_real[3][0], -1));
    assert(is_equal(s3.points_real[3][1],  2));
    std::cout << "[SHAPE]\t\tOK - Rotate matrix" << std::endl;


    Shape s4(std::vector<Point>{
        Point(1, 1),
        Point(1, 2),
        Point(2, 2),
        Point(2, 1)
    });
    s4.translate(10, 3);
    assert(s4.points_real[0] == Point(11, 4));
    assert(s4.points_real[1] == Point(11, 5));
    assert(s4.points_real[2] == Point(12, 5));
    assert(s4.points_real[3] == Point(12, 4));
    std::cout << "[SHAPE]\t\tOK - Translate matrix" << std::endl;


    Shape s5(std::vector<Point>{
        Point(1, 1),
        Point(1, 2),
        Point(2, 2),
        Point(2, 1)
    });
    assert(s5.medium() == Point(1.5, 1.5));
    std::cout << "[SHAPE]\t\tOK - Medium point" << std::endl;

}

}  // namespace Test

#endif  // TEST_SHAPE_H
