#ifndef TEST_DRAWABLE_H
#define TEST_DRAWABLE_H

#include <assert.h>

#include <drawable.h>

namespace Test {

void compare(const Matrix& m0, const Matrix& m1) {
    for (int i = 0; i < m0.size(); i++) {
        for (int j = 0; j < m0.size(); j++) {
            assert(m0[i][j] == m1[i][j]);
        }
    }
}

void test_drawable() {

    const Matrix translate{
        std::vector<double>{1, 0, 0},
        std::vector<double>{0, 1, 0},
        std::vector<double>{5, 3, 1}
    };
    const std::vector<double> v_translate{5, 3};
    compare(translate, Drawable::translate_matrix(v_translate));
    std::cout << "[Drawable] OK - Translate matrix" << std::endl;


    const Matrix scale{
        std::vector<double>{5, 0, 0},
        std::vector<double>{0, 7, 0},
        std::vector<double>{0, 0, 1}
    };
    const std::vector<double> s = std::vector<double>{5, 7};
    compare(Drawable::scale_matrix(s), scale);
    std::cout << "[Drawable] OK - Scale matrix" << std::endl;


    const Matrix rotate{
        std::vector<double>{5, 0, 0},
        std::vector<double>{0, 7, 0},
        std::vector<double>{0, 0, 1}
    };
    std::cout << "[Drawable] OK - Scale matrix" << std::endl;


    const Point p0(5, 5);
    const Matrix m0{
        std::vector<double>{1, 0, 0},
        std::vector<double>{0, 1, 0},
        std::vector<double>{5, 5, 1}
    };
    const Point r0 = Drawable::p_multiply(p0, m0);
    assert(r0[0] == 10);
    assert(r0[1] == 10);
    std::cout << "[Drawable] OK - Point multiply" << std::endl;


    const Matrix multiply0{
        std::vector<double>{1, 1, 2},
        std::vector<double>{2, 2, 3},
        std::vector<double>{3, 1, 3}
    };
    const Matrix multiply1{
        std::vector<double>{2, 1, 3},
        std::vector<double>{1, 1, 3},
        std::vector<double>{3, 2, 3}
    };
    const Matrix r_multiply{
        std::vector<double>{9, 6, 12},
        std::vector<double>{15, 10, 21},
        std::vector<double>{16, 10, 21}
    };
    const Matrix res_mult = Drawable::m_multiply(multiply0, multiply1);
    compare(res_mult, r_multiply);
    std::cout << "[Drawable] OK - Matrix multiply" << std::endl;

}

}  // namespace Test

#endif  // TEST_DRAWABLE_H