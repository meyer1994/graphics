#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

// Better reading
typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;

// Constant
const double _MATH_PI = std::acos(-1.0);


namespace Transformation {

const Matrix scale(double x, double y, double z) {
    return Matrix{
    	Vector{x, 0, 0, 0},
    	Vector{0, y, 0, 0},
    	Vector{0, 0, z, 0},
    	Vector{0, 0, 0, 1}
    };
}

const Matrix rotatex(double angle) {
    double radian = (angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{1,  0, 0, 0},
        Vector{0,  c, s, 0},
        Vector{0, -s, c, 0},
        Vector{0,  0, 0, 1}
    };
}

const Matrix rotatey(double angle) {
    double radian = (angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{c, 0, -s, 0},
        Vector{0, 1,  0, 0},
        Vector{s, 0,  c, 0},
        Vector{0, 0,  0, 1}
    };
}

const Matrix rotatez(double angle) {
    double radian = (angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{ c, s, 0, 0},
        Vector{-s, c, 0, 0},
        Vector{ 0, 0, 1, 0},
        Vector{ 0, 0, 0, 1}
    };
}

const Matrix translate(double x, double y, double z) {
    return Matrix{
    	Vector{1, 0, 0, 0},
    	Vector{0, 1, 0, 0},
    	Vector{0, 0, 1, 0},
    	Vector{x, y, z, 1}
    };
}

const Matrix multiply(const Matrix& m0, const Matrix& m1) {
	if (m0.size() != m1.size()) {
		throw std::invalid_argument("Matrices should be of same size");
	}

	int total = m0.size();
	Matrix res(total, Vector(total, 0));

	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total; j++) {
			for (int k = 0; k < total; k++) {
				res[i][j] += (m0[i][k] * m1[k][j]);
			}
		}
	}

	return res;
}

Vector multiply(const Vector& line, const Matrix& matrix) {
	if (line.size() != matrix.size()) {
		throw std::invalid_argument("Line must have same number of columns"
									" as the matrix has lines");
	}

	// Column of 0s
	Vector result(line.size(), 0);
	int total = line.size();

	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total; j++) {
			result[i] += line[j] * matrix[j][i];
		}
	}

	return result;
}

Vector multiply(const Matrix& matrix, const Vector& column) {
	if (matrix.size() != column.size()) {
		throw std::invalid_argument("Column must have same number of lines"
									" as the matrix has columns");
	}

	// Column of 0s
	Vector result(column.size(), 0);
	int total = column.size();

	for (int i = 0; i < total; i++) {
		for (int j = 0; j < total; j++) {
			result[i] += matrix[i][j] * column[j];
		}
	}

	return result;
}

double multiply(const Vector& v0, const Vector& v1) {
	if (v0.size() != v1.size()) {
		throw std::invalid_argument("Vectors must be of same size");
	}

	double result = 0;
	for (int i = 0; i < v0.size(); i++) {
		result += v0[i] * v1[i];
	}

	return result;
}

}  // namespace Transformation


class Point : public Vector {
public:
    Point() : Vector{0, 0, 0} {}

    explicit Point(Vector coords) : Vector(coords) {}

    Point(double x, double y, double z = 0) : Vector{x, y, z} {}

    void transform(const Matrix& m) {
        // Temporary point to store new values
        Vector temp{0, 0, 0, 1};

        // Add one to end
        push_back(1);

        // Apply transformation matrix to point (multiply the matrices)
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                temp[i] += (at(j) * m[j][i]);
            }
        }

        // Copy new values to this point
        *this = Point(temp);

        // Remove 1 from end
        pop_back();
        shrink_to_fit();
    }

    const std::string to_string() const {
        if (size() == 0) {
            return "Point()";
        }

        std::string str = "Point(";
        for (int i = 0; i < size() - 1; i++) {
            str += std::to_string(at(i)) + ", ";
        }
        str += std::to_string(back()) + ")";

        return str;
    }
};

#endif  // POINT_H
