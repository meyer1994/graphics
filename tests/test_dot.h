#ifndef TEST_DOT_H
#define TEST_DOT_H

#include <iostream>
#include <assert.h>

#include <dot.h>

namespace Test {

void test_dot() {

    Dot d0;
    assert(d0.point.size() == 0);
    std::cout << "[Dot] OK - Default constructor" << std::endl;


    Dot d1(1, 2);
    assert(d1.point.size() == 3);
    std::cout << "[Dot] OK - 2D constructor" << std::endl;

    
    Dot d2(1, 2, 3);
    assert(d2.point.size() == 4);
    std::cout << "[Dot] OK - 3D constructor" << std::endl;


    Dot d3(45, 50, 2);
    assert(d3.point == Point(45, 50, 2));
    std::cout << "[Dot] OK - Medium point" << std::endl;


    d3.scale(5);
    assert(d3.point == Point(45, 50, 2));
    std::cout << "[Dot] OK - Scale" << std::endl;


    Dot d4(45, 50);
    std::string str = "Dot(";
    str.append("Point(");
    str.append(std::to_string(45.0));
    str.append(", ");
    str.append(std::to_string(50.0));
    str.append("))");
    assert(d4.to_string() == str);
    std::cout << "[Dot] OK - To string (not empty)" << std::endl;


    assert(d0.to_string() == "Dot()");
    std::cout << "[Dot] OK - To string (empty)" << std::endl;


    Dot d5(50, 0);
    d5.rotate(-90);
    std::cout << "[Dot] OK - Rotate" << std::endl;

}

}  // namespace Test

#endif  // TEST_DOT_H