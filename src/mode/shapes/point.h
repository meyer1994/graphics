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

/**
 * @brief Static scale matrix method.
 *
 * @details Returns an scale matrix to be used in transform operations.
 *
 * @param v Vector containing the values to scale dimensions.
 *
 * @return Matrix of size `v.size() + 1`, of the transformation.
 */
Matrix scale(const Vector& v) {
    int total = v.size();

    // Matrix of zeroes
    Matrix matrix(total + 1, Vector(total + 1, 0));

    // Add ratios to main diagonal
    for (int i = 0; i < total; i++) {
        matrix[i][i] = v[i];
    }

    // Add 1 to last cell
    matrix[total][total] = 1;

    return matrix;
}

/**
 * @brief Static rotate matrix method (only works for 2D).
 *
 * @details Returns an rotate matrix to be used in transform operations.
 *
 * @param angle Angle to rotate matrix from origin.
 *
 * @return Matrix of size `(3 x 3)`, of the transformation.
 */
Matrix rotate(double angle) {
    double radian = (-angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{c, -s, 0},
        Vector{s,  c, 0},
        Vector{0,  0, 1}
    };
}

Matrix rotatex(double angle) {
    double radian = (-angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{1,  0, 0, 0},
        Vector{0,  c, s, 0},
        Vector{0, -s, c, 0},
        Vector{0,  0, 0, 1}
    };
}

Matrix rotatey(double angle) {
    double radian = (-angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{c, 0, -s, 0},
        Vector{0, 1,  0, 0},
        Vector{s, 0,  c, 0},
        Vector{0, 0,  0, 1}
    };
}

Matrix rotatez(double angle) {
    double radian = (-angle * _MATH_PI) / 180;
    double c = std::cos(radian);
    double s = std::sin(radian);
    return Matrix{
        Vector{c, -s, 0, 0},
        Vector{s,  c, 0, 0},
        Vector{0,  0, 1, 0},
        Vector{0,  0, 0, 1}
    };
}

/**
 * @brief Static translate matrix method.
 *
 * @details Returns an translate matrix to be used in transform operations.
 *
 * @param v Vector containing the values to translate each coordinate.
 *
 * @return Matrix of size `v.size() + 1`, of the transformation.
 */
Matrix translate(const Vector& v) {
    int total = v.size();

    // Matrix of zeroes
    Matrix matrix(total + 1, Vector(total + 1, 0));

    // Add 1s to main diagonal
    for (int i = 0; i < total + 1; i++) {
        matrix[i][i] = 1;
    }

    // Add translation line
    for (int i = 0; i < total; i++) {
        matrix[total][i] = v[i];
    }

    return matrix;
}

Matrix combine(const Matrix& m0, const Matrix& m1) {
    if (m0.size() != m1.size()) {
        throw std::invalid_argument("Matrices should be of same size");
    }

    int total = m0.size();

    // Matrix of zeroes
    Matrix result(total, Vector(total, 0));

    // Multiply matrices
    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
            for (int k = 0; k < total; k++) {
                result[i][j] += (m0[i][k] * m1[k][j]);
            }
        }
    }

    return result;
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
    /**
     * @brief Default constructor.
     *
     * @details Instantiate an empty point, with no coordinates whatsoever.
     */
    Point() : Vector() {}

    /**
     * @brief Explicit constructor.
     *
     * @details Creates a point with the coordinates passed into as a vector.
     * This means, coords[0] is X, coords[1] is Y and so on. The dimension of
     * the point is determined by the size of this vector.
     *
     * @param coords Vector of doubles to be used as coordinates in the space.
     */
    explicit Point(Vector coords) : Vector(coords) {
        if (coords.size() < 2) {
            throw std::invalid_argument("Point must have, at least, 2 dimensions");
        }
    }

    /**
     * @brief 2D point constructor.
     *
     * @details Utility constructor to easily create a 2D point. Is the same as
     * calling Point(Vector{x, y}).
     *
     * @param x X coordinate in space.
     * @param y Y coordinate in space
     */
    Point(double x, double y) : Vector() {
        push_back(x);
        push_back(y);
    }

    /**
     * @brief 3D point constructor.
     *
     * @details Utility constructor to easily create a 3D point. Is the same as
     * calling Point(Vector{x, y, z}).
     *
     * @param x X coordinate in space.
     * @param y Y coordinate in space.
     * @param z Z coordinate in space.
     */
    Point(double x, double y, double z) : Vector() {
        push_back(x);
        push_back(y);
        push_back(z);
    }

    /**
     * @brief Scale the point from the origin.
     *
     * @details Will multiply all the point coordinates by the desired ratio.
     * A consequence of this approach is that it will make points get further
     * away from the origin, (0, 0), when used.
     *
     * @param ratio By how much do you want to scale the point's coordinates.
     */
    const Point& scale(double ratio) {
        Vector r(size(), ratio);
        Matrix s = Transformation::scale(r);
        transform(s);
        return *this;
    }

    /**
     * @brief Rotate the point based on the origin.
     *
     * @details Rotate the point by the angle passed. It follows the principle
     * of the unit circle. Which means, if you rotate it 90 degrees, it will
     * rotate it in an anti-clockwise fashion.
     *
     * Example:
     * ```{.cpp}
     * Point p(5, 0);
     * p.rotate(90);
     * // p is now (0, 5)
     * ```
     *
     * @param angle The angle, in degrees,you want to rotate.
     */
    const Point& rotate(double angle) {
        Matrix r = Transformation::rotate(angle);
        transform(r);
        return *this;
    }

    /**
     * @brief Translate point.
     *
     * @details Will simply sum the values passed with the correspondend
     * coordiante values.
     *
     * @param v Vector with the values to be summed with the coordinates.
     */
    const Point& translate(const Vector& v) {
        Matrix t = Transformation::translate(v);
        transform(t);
        return *this;
    }

    /**
     * @brief Transform function.
     *
     * @details Applies the transformation matrix passed to the point. Very
     * useful when there is the need for more than one transformation at one
     * time. It simply multiplies the point with the matrix passed as argument.
     *
     * @param m Matrix to transform point with.
     */
    const Point& transform(const Matrix& m) {
        // Temporary point to store new values
        Point temp(Vector(size() + 1, 0));

        // Add 1 to end of point for easier transformations
        push_back(1);

        // Apply transformation matrix to point (multiply the matrices)
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                temp[i] += (at(j) * m[j][i]);
            }
        }

        // Copy new values to this point
        *this = temp;

        // Remove 1 from end
        pop_back();

        return *this;
    }

    /**
     * @brief To string method.
     *
     * @details Makes a representation of the point. For easier debugging.
     *
     * @return String in the form of `Point(x, y, ...)`.
     */
    const std::string to_string() const {
        if (size() == 0) {
            return "Point()";
        }

        std::string str = "Point(";
        for (int i = 0; i < size() - 1; i++) {
            str.append(std::to_string(at(i)));
            str.append(", ");
        }
        str.append(std::to_string(back()));
        str.append(")");
        return str;
    }
};

#endif  // POINT_H
