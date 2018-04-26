#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

class Matrix;

class Vector : public std::vector<double> {
public:
	Vector() : std::vector<double>() {}

	Vector(int size, double value) : std::vector<double>(size, value) {}

	Vector(std::initializer_list<double> d) : std::vector<double>(d) {}

	Vector(std::vector<double> v) : std::vector<double>(v) {}

	virtual ~Vector() {}

	const double length() const {
		double l = 0;
		for (int i  = 0; i < size(); i++) {
			l += at(i) * at(i);
		}
		return std::sqrt(l);
	}

	const double angle(const Vector& v) const {
		// Vector calculations
		double dot = (*this) * v;
		double val = v.length();
		double vbl = length();

		// Apply to formula
		double cos = dot / (val * vbl);
		double a = std::acos(cos);

		// Convert to degrees
		return (180.0 / std::acos(-1.0)) * a;
	}

	const Vector unit() const {
		double len = length();
		Vector u;
		for (int i = 0; i < size(); i++) {
			u.push_back(at(i) / len);
		}
		return u;
	}

	const double operator*(const Vector& v) const {
		if (size() != v.size()) {
			throw std::invalid_argument("Vectors should be of same size");
		}

		double result = 0;
		for (int i = 0; i < size(); i++) {
			result += (at(i) * v[i]);
		}
		return result;
	}

	const Vector operator*(const double d) const {
		Vector v(*this);
		for (double& i : v) {
			i *= d;
		}
		return v;
	}

	const Vector operator*(const Matrix& m) const;

	const bool operator==(const Vector& v) const {
		if (size() != v.size()) {
			return false;
		}

		for (int i = 0; i < size(); i++) {
			if (at(i) != v[i]) {
				return false;
			}
		}

		return true;
	}

	const std::string to_string() const {
		if (empty()) {
			return std::string("Vector()");
		}

		std::string str = "Vector(";
		for (int i = 0; i < size() - 1; i++) {
			double d = at(i);
			str += std::to_string(d) + ", ";
		}
		double last = back();
		return str + std::to_string(last) + ")";
	}
};

class Matrix : public std::vector<Vector> {
public:
	Matrix() : std::vector<Vector>() {}

	Matrix(int size, Vector vec) : std::vector<Vector>(size, vec) {}

	Matrix(std::initializer_list<Vector> d) : std::vector<Vector>(d) {}

	Matrix(std::vector<Vector> v) : std::vector<Vector>(v) {}

	virtual ~Matrix() {}

	const Vector operator*(const Vector& v) const {
		if (size() != v.size()) {
			throw std::invalid_argument("Vector must have same number of values as the matrix has columns");
		}

		// Vector of zeroes
		Vector result(v.size(), 0);
		int total = v.size();

		for (int i = 0; i < total; i++) {
			for (int j = 0; j < total; j++) {
				result[i] += at(i)[j] * v[j];
			}
		}

		return result;
	}

	const Matrix operator*(const double d) const {
		Matrix m(*this);
		for (Vector& v : m) {
			v = v * d;
		}
		return m;
	}

	const Matrix operator*(const Matrix& m) const {
		if (size() != m.size()) {
			throw std::invalid_argument("Matrices should be of same size");
		}

		int total = size();
		Matrix res(total, Vector(total, 0));

		for (int i = 0; i < total; i++) {
			for (int j = 0; j < total; j++) {
				for (int k = 0; k < total; k++) {
					res[i][j] += (at(i)[k] * m[k][j]);
				}
			}
		}

		return res;
	}

	const bool operator==(const Matrix& m) const {
		if (size() != m.size()) {
			return false;
		}

		for (int i = 0; i < size(); i++) {
			if (at(i) != m[i]) {
				return false;
			}
		}

		return true;
	}

	const std::string to_string() const {
		if (empty()) {
			return std::string("Matrix()");
		}

		std::string str = "Matrix(";
		for (int i = 0; i < size() - 1; i++) {
			const Vector& v = at(i);
			str += v.to_string() + ", ";
		}
		const Vector& last = back();
		return str + last.to_string() + ")";
	}
};

///////////////////////////
//                       //
// THIS IS VERY STUPID!! //
// WHY C++? WHY!?!       //
//                       //
///////////////////////////
const Vector Vector::operator*(const Matrix& m) const {
	int total = size();

	if (total != m.size()) {
		throw std::invalid_argument("Vector and matrix should match sizes");
	}

	// Column of 0s
	Vector result(total, 0);

	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total; j++) {
			result[i] += at(j) * m[j][i];
		}
	}

	return result;
}

#endif  // VECTOR_H
