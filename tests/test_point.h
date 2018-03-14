#ifndef TEST_POINT_H
#define TEST_POINT_H

#include <iostream>
#include <assert.h>

#include <point.h>

namespace Test {

void point() {
    Point p0;
    assert(p0.size() == 0);
    std::cout << "[POINT]\t\tOK - default constructor" << std::endl;


    Point p1(std::vector<double>{1, 2, 3});
    assert(p1.size() == 4);
    assert(p1[0] == 1);
    assert(p1[1] == 2);
    assert(p1[2] == 3);
    std::cout << "[POINT]\t\tOK - explicit constructor" << std::endl;


    Point p2(1, 2);
    assert(p2.size() == 3);
    assert(p2[0] == 1);
    assert(p2[1] == 2);
    std::cout << "[POINT]\t\tOK - 2D constructor" << std::endl;

}

}  // namespace Test

#endif  // TEST_POINT_H
