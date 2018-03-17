#ifndef TEST_UTIL_H
#define TEST_UTIL_H

namespace Test {

bool is_equal(double x, double y) {
    const double e = 1e-15;
    return std::abs(x - y) <= e;
}

void compare_matrix(Matrix& m0, Matrix& m1) {
    assert(m0.size() == m1.size());

    for (int i = 0; i < m0.size(); i++) {
        assert(m0[i].size() == m1[i].size());
    }

    for (int i = 0; i < m0.size(); i++) {
        for (int j = 0; j < m0.size(); j++) {
            assert(is_equal(m0[i][j], m1[i][j]));
        }
    }
}

}  // namespace Test

#endif // TEST_UTIL_H