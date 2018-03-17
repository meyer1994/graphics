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
    assert(d1.points_real[0].size() == 2);
    std::cout << "[DOT]\t\tOK - 2D constructor" << std::endl;


    Dot d2(45, 50);
    assert(d2.medium() == Point(45, 50));
    std::cout << "[DOT]\t\tOK - Medium point" << std::endl;


    Dot d3(45, 50);
    d3.translate(15, 10);
    assert(d3.points_real[0] == Point(60, 60));
    std::cout << "[DOT]\t\tOK - Translate" << std::endl;


    Dot d4(20, 35);
    d4.scale(3);
    assert(d4.points_real[0] == Point(60, 105));
    std::cout << "[DOT]\t\tOK - Scale" << std::endl;


    Dot d5(50, 0);
    d5.rotate(90);
    assert(std::round(d5.points_real[0][0]) == 0);
    assert(std::round(d5.points_real[0][1]) == 50);
    std::cout << "[DOT]\t\tOK - Rotate" << std::endl;

}

}  // namespace Test

#endif  // TEST_DOT_H
