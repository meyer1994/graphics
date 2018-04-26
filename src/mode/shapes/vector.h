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

	static const double length(const Vector& v) {
		double l = 0;
		for (int i  = 0; i < v.size(); i++) {
			l += v[i] * v[i];
		}
		return std::sqrt(l);
	}

	const double length() const {
		return length(*this);
	}

	static const double angle(const Vector& v0, const Vector& v1) {
		// Vector calculations
		double dot = v0 * v1;
		double val = v1.length();
		double vbl = v0.length();

		// Apply to formula
		double cos = dot / (val * vbl);
		double a = std::acos(cos);

		// Convert to degrees
		return (180.0 / std::acos(-1.0)) * a;
	}

	const double angle(const Vector& v) const {
		return angle(*this, v);
	}

	static const Vector unit(const Vector& v) {
		double len = v.length();
		Vector u;
		for (int i = 0; i < v.size(); i++) {
			u.push_back(v[i] / len);
		}
		return u;
	}

	const Vector unit() const {
		return unit(*this);
	}

	static const Vector cross(const Vector& v0, const Vector& v1) {
		if (v1.size() != v0.size()) {
			throw std::invalid_argument("Vectors should be of same size");
		}

		if (v1.size() != 3) {
			throw std::invalid_argument("Vectors should have size 3");
		}

		Vector result(3, 0);
		result[0] =   (v0[1] * v1[2]) - (v0[2] * v1[1]);
		result[1] = -((v0[0] * v1[2]) - (v0[2] * v1[0]));
		result[2] =   (v0[0] * v1[1]) - (v0[1] * v1[0]);
		return result;
	}

	const Vector cross(const Vector& v) const {
		return cross(*this, v);
	}

	const Vector operator+(const Vector& v) const {
		if (size() != v.size()) {
			throw std::invalid_argument("Vectors should be of same size");
		}

		Vector result(size(), 0);
		for (int i = 0; i < size(); i++) {
			result[i] = at(i) + v[i];
		}
		return result;
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
