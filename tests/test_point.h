#ifndef TEST_POINT_H
#define TEST_POINT_H

#include <iostream>
#include <vector>
#include <assert.h>

#include <point.h>

namespace Test {

void test_point() {
    Point p0;
    assert(p0.size() == 0);
    std::cout << "[Point] OK - default constructor" << std::endl;


    Point p1(std::vector<double>{1, 2, 3});
    assert(p1.size() == 4);
    assert(p1[0] == 1);
    assert(p1[1] == 2);
    assert(p1[2] == 3);
    std::cout << "[Point] OK - explicit constructor" << std::endl;


    Point p2(1, 2);
    assert(p2.size() == 3);
    assert(p2[0] == 1);
    assert(p2[1] == 2);
    std::cout << "[Point] OK - 2D constructor" << std::endl;

    Point p3(1, 2, 3);
    assert(p3.size() == 4);
    assert(p3[0] == 1);
    assert(p3[1] == 2);
    assert(p3[2] == 3);
    std::cout << "[Point] OK - 2D constructor" << std::endl;


    Point p4(1, 2);
    assert(p4.size() == 3);
    std::string str = "Point(";
    str.append(std::to_string(1.0));
    str.append(", ");
    str.append(std::to_string(2.0));
    str.append(")");
    assert(p4.to_string() == str);
    std::cout << "[Point] OK - To string (not empty)" << std::endl;


    Point p5;
    assert(p5.size() == 0);
    assert(p5.to_string().size() > 0);
    assert(p5.to_string() == "Point()");
    std::cout << "[Point] OK - To string (empty)" << std::endl;
}

}  // namespace Test

#endif  // TEST_POINT_H