#ifndef TEST_POLYGON_H
#define TEST_POLYGON_H

#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

#include <polygon.h>

namespace Test {

void test_polygon() {
    
    Polygon p0;
    assert(p0.points.size() == 0);
    std::cout << "[Polygon] OK - Default constructor" << std::endl;


    Polygon poly(std::vector<Point>{
        Point(1, 1),
        Point(1, 2),
        Point(2, 2),
        Point(2, 1)
    });
    poly.rotate(-90);
    std::cout << poly.to_string() << std::endl;
    std::cout << "[Polygon] OK - Rotate" << std::endl;

}

}  // namespace Test

#endif  // TEST_POLYGON_H