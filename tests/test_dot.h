#ifndef TEST_DOT_H
#define TEST_DOT_H

#include <iostream>
#include <cmath>
#include <assert.h>

#include <dot.h>

namespace Test {

void dot() {

    Dot d0;
    assert(d0.size() == 0);
    std::cout << "[DOT]\t\tOK - Default constructor" << std::endl;


    Dot d1(1, 2);
    assert(d1.points_real[0].dimensions() == 2);
    std::cout << "[DOT]\t\tOK - 2D constructor" << std::endl;


    Dot d2(45, 50);
    assert(d2.points_real[0] == Point(45, 50));
    std::cout << "[DOT]\t\tOK - Medium point" << std::endl;


    Dot d3(20, 35);
    d3.scale(3);
    assert(d3.points_real[0] == Point(60, 105));
    std::cout << "[DOT]\t\tOK - Scale" << std::endl;


    Dot d5(50, 0);
    d5.rotate(-90);
    assert(std::round(d5.points_real[0][0]) == 0);
    assert(std::round(d5.points_real[0][1]) == 50);
    std::cout << "[DOT]\t\tOK - Rotate" << std::endl;

}

}  // namespace Test

#endif  // TEST_DOT_H
