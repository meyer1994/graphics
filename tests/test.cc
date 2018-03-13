#include "test_point.h"
#include "test_drawable.h"
#include "test_line.h"
#include "test_dot.h"
#include "test_polygon.h"

int main(int argc, char* argv[]) {

    Test::test_point();
    Test::test_drawable();
    Test::test_dot();
    Test::test_line();
    Test::test_polygon();


    // std::cout << "Move square to (0,0)" << std::endl;
    // square.move(0, 0);
    // Point p1 = square.get_medium_point();
    // assert(p1.x == 0);
    // assert(p1.y == 0);
    
    // square.move(5, 5);
    // Point p2 = square.get_medium_point();
    // std::cout << "Move square to (5, 5)" << std::endl;
    // print_p(p2);
    // assert(p2.x == 5);
    // assert(p2.y == 5);

    // square.translate(5, 5);
    // Point p5 = square.get_medium_point();
    // std::cout << "Translating square to (10, 10)" << std::endl;
    // print_p(p5);
    // assert(p5.x == 10);
    // assert(p5.y == 10);

    // square.move(1, 1);
    // std::cout << "Scale square 2x" << std::endl;
    // square.scale(2);
    // Point p3 = square.get_medium_point();
    // assert(p3.x == 2);
    // assert(p3.y == 2);
    // print_points(square.points);

    // square.scale(0.5);
    // square.inflate(2);
    // std::cout << "Infalte square 2x" << std::endl;
    // Point p4 = square.get_medium_point();
    // assert(p4.x == 1);
    // assert(p4.y == 1);
    // print_points(square.points);

}