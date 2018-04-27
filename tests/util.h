#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <cmath>

#include <line.h>
#include <polygon.h>
#include <vector.h>

bool is_equal(double x, double y) {
    const double e = 1e-5;
    return std::abs(x - y) <= e;
}

bool compare(const Vector& a, const Vector& b) {
	if (a.size() != b.size()) {
		return false;
	}

	for (int i = 0; i < a.size(); i++) {
		if (!is_equal(a[i], b[i])) {
			return false;
		}
	}

	return true;
}

bool compare(const std::vector<Point>& v0, const std::vector<Point>& v1) {
	if (v0.size() != v1.size()) {
		return false;
	}

	for (int i = 0; i < v0.size(); i++) {
		const Point& a = v0[i];
		const Point& b = v1[i];
		if (!compare(a, b)) {
			return false;
		}
	}

	return true;
}

bool compare(const Matrix& m0, const Matrix& m1) {
    if (m0.size() != m1.size()) {
    	return false;
    }

    for (int i = 0; i < m0.size(); i++) {
    	if (!compare(m0[i], m1[i])) {
    		return false;
    	}
    }

    return true;
}

bool compare(const Shape& s0, const Shape& s1) {
	return compare(s0.real, s1.real) && compare(s0.medium , s1.medium);
}

#endif // TEST_UTIL_H
