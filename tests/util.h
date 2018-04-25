#ifndef TEST_UTIL_H
#define TEST_UTIL_H

bool is_equal(double x, double y) {
    const double e = 1e-10;
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

bool compare(const Line& la, const Line& lb) {
	return compare(la.a, lb.a) && compare(la.b, lb.b) && compare(la.medium, lb.medium);
}

bool compare(const Polygon& pa, const Polygon& pb) {
	if (pa.lines.size() != pb.lines.size()) {
		return false;
	}

	if (!compare(pa.medium, pb.medium)) {
		return false;
	}

	for (int i = 0; i < pa.lines.size(); i++) {
		const Line& la = pa.lines[i];
		const Line& lb = pb.lines[i];
		if (!compare(la, lb)) {
			return false;
		}
	}


	return true;
}

#endif // TEST_UTIL_H
