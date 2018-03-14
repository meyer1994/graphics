#ifndef TEST_LINE_H
#define TEST_LINE_H

#include <iostream>
#include <assert.h>

#include <line.h>

namespace Test {

void line() {

    Line l0;
    assert(l0.size() == 0);
    std::cout << "[LINE]\t\tOK - Default constructor" << std::endl;


    Point a(0, 0);
    Point b(10, 0);
    Line l1(a, b);
    assert(l1.points_real[0].dimensions() == 2);
    assert(l1.points_real[1].dimensions() == 2);
    assert(l1.points_real[0] == a);
    assert(l1.points_real[1] == b);
    std::cout << "[LINE]\t\tOK - 2 point constructor" << std::endl;


    Point m = l1.medium();
    assert(m.dimensions() == 2);
    assert(m[0] == 5);
    assert(m[1] == 0);
    std::cout << "[LINE]\t\tOK - Medium point" << std::endl;


    Line l3(Point(0, 0), Point(10, 0));
    l3.translate(10, 5);
    assert(l3.points_real[0][0] == 10);
    assert(l3.points_real[0][1] == 5);
    assert(l3.points_real[1][0] == 20);
    assert(l3.points_real[1][1] == 5);
    std::cout << "[LINE]\t\tOK - Translate matrix" << std::endl;


    Line l4(Point(0, 0), Point(10, 10));
    l4.scale(2);
    assert(l4.points_real[0] == Point(0, 0));
    assert(l4.points_real[1] == Point(20, 20));
    std::cout << "[LINE]\t\tOK - Scale matrix" << std::endl;


    Line l5(Point(0, 0), Point(5, 0));
    l5.rotate(-90);
    assert(l5.points_real[0] == Point(0, 0));
    std::cout << "[LINE]\t\tOK - Rotate matrix" << std::endl;
}

}  // namespace Test

#endif  // TEST_LINE_H
