#include <vector>
#include <iostream>
#include <assert.h>
#include "src/mode/drawable.h"

void print_p(Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}

void print_points(const std::vector<Point>& v) {
    for (Point p : v)
        print_p(p);
}

int main(int argc, char* argv[]) {
    Drawable square(std::vector<Point>{
        Point(0, 0),
        Point(0, 2),
        Point(2, 2),
        Point(2, 0),
    });

    std::cout << "First medium point" << std::endl;
    Point p0 = square.get_medium_point();
    assert(p0.x == 1);
    assert(p0.y == 1);

    std::cout << "Move square to (0,0)" << std::endl;
    square.move(0, 0);
    Point p1 = square.get_medium_point();
    assert(p1.x == 0);
    assert(p1.y == 0);
    
    square.move(5, 5);
    Point p2 = square.get_medium_point();
    std::cout << "Move square to (5, 5)" << std::endl;
    print_p(p2);
    assert(p2.x == 5);
    assert(p2.y == 5);

    square.translate(5, 5);
    Point p5 = square.get_medium_point();
    std::cout << "Translating square to (10, 10)" << std::endl;
    print_p(p5);
    assert(p5.x == 10);
    assert(p5.y == 10);

    square.move(1, 1);
    std::cout << "Scale square 2x" << std::endl;
    square.scale(2);
    Point p3 = square.get_medium_point();
    assert(p3.x == 2);
    assert(p3.y == 2);
    print_points(square.points);

    square.scale(0.5);
    square.inflate(2);
    std::cout << "Infalte square 2x" << std::endl;
    Point p4 = square.get_medium_point();
    assert(p4.x == 1);
    assert(p4.y == 1);
    print_points(square.points);

}