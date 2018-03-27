#include "test_point.h"
#include "test_shape.h"
#include "test_dot.h"
#include "test_line.h"
#include "test_descriptor.h"

int main(int argc, char* argv[]) {

    Test::point();
    std::cout << "==========" << std::endl;
    Test::shape();
    std::cout << "==========" << std::endl;
    Test::dot();
    std::cout << "==========" << std::endl;
    Test::line();
    std::cout << "==========" << std::endl;
    Test::write();
    std::cout << "==========" << std::endl;
    Test::read();

}
