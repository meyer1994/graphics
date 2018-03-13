#ifndef TEST_LINE_H
#define TEST_LINE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

#include <line.h>

namespace Test {

void test_line() {
    
    Line l0;
    assert(l0.a.size() == 0);
    assert(l0.b.size() == 0);
    std::cout << "[Line] OK - Default constructor" << std::endl;


    Point a(0, 0);
    Point b(10, 0);
    Line l1(a, b);
    assert(l1.a.size() == 3);
    assert(l1.b.size() == 3);
    assert(l1.a == a);
    assert(l1.b == b);
    std::cout << "[Line] OK - 2 point constructor" << std::endl;


    Point m = l1.medium();
    assert(m.size() == 3);
    assert(m[0] == 5);
    assert(m[1] == 0);
    std::cout << "[Line] OK - Medium point" << std::endl;


    std::string str = "Line(";
    str.append(l1.a.to_string());
    str.append(", ");
    str.append(l1.b.to_string());
    str.append(")");
    assert(l1.to_string() == str);
    std::cout << "[Line] OK - To string (not empty)" << std::endl;


    Line l2;
    assert(l2.to_string() == "Line()");
    std::cout << "[Line] OK - To string (empty)" << std::endl;


    Line l3(Point(0, 0), Point(10, 0));
    l3.translate(10, 5);
    assert(l3.a[0] == 10);
    assert(l3.a[1] == 5);
    assert(l3.b[0] == 20);
    assert(l3.b[1] == 5);
    std::cout << "[Line] OK - Translate matrix" << std::endl;


    Line l4(Point(0, 0), Point(10, 10));
    l4.scale(2);
    assert(l4.a == Point(0, 0));
    assert(l4.b == Point(20, 20));
    std::cout << "[Line] OK - Scale matrix" << std::endl;


    Line l5(Point(0, 0), Point(5, 0));
    l5.rotate(-90);
    assert(l5.a == Point(0, 0));
    std::cout << "[Line] OK - Rotate matrix" << std::endl;

}

}  // namespace Test

#endif  // TEST_LINE_H