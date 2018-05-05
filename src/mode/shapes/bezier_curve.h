#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>

#include "point.h"
#include "shape.h"

class BezierCurve : public Shape {
public:
	BezierCurve() : Shape("bezier_curve") {}

	BezierCurve(std::string name) : Shape(name) {}

	BezierCurve(std::initializer_list<Point> d)
	: Shape(d, "bezier_curve") {
		int size = real.size();
		if (size < 4 || size % 3 != 1) {
			throw std::invalid_argument("Points size must obey { size % 3 == 1 }");
		}

		blending_function(std::vector<Point>(d));
	}

	BezierCurve(std::vector<Point> points, double t, std::string name = "bezier_curve")
	: Shape(points, name),
	  t(t) {
		int size = real.size();
		if (size < 4 || size % 3 != 1) {
			throw std::invalid_argument("Points size must obey { size % 3 == 1 }");
		}

		blending_function(points);
	}

	virtual ~BezierCurve() {}

	virtual const std::string to_string() const override {
		if (real.empty()) {
			return std::string("BezierCurve()");
		}

		std::string str = "BezierCurve(";
		for (int i = 0; i < real.size() - 1; i++) {
			const Point& p = real[i];
			str += p.to_string() + ", ";
		}
		const Point& last = real.back();
		str += last.to_string() + ")";
		return str;
	}

    virtual const ShapeType type() const override {
        return ShapeType::BezierCurve;
    }

	double t = 0.05;

protected:
	const Matrix magic{
		Vector{-1.0,  3.0, -3.0, 1.0},
		Vector{ 3.0, -6.0,  3.0, 0.0},
		Vector{-3.0,  3.0,  0.0, 0.0},
		Vector{ 1.0,  0.0,  0.0, 0.0}
	};

	const Vector t_vector(const double tee) {
		return Vector{
			tee * tee * tee,
			tee * tee,
			tee,
			1
		};
	}

	void blending_function(const std::vector<Point> v) {
		double temp_t = t;
		real.clear();

		for (int i = 0; i < v.size() - 1; i += 3) {
			// Get points
			const Point& p0 = v[i];
			const Point& p1 = v[i + 1];
			const Point& p2 = v[i + 2];
			const Point& p3 = v[i + 3];

			// Vectors
			const Vector x_vector{p0[0], p1[0], p2[0], p3[0]};
			const Vector y_vector{p0[1], p1[1], p2[1], p3[1]};
			const Vector z_vector{p0[2], p2[2], p2[2], p3[2]};

			while (temp_t <= 1) {
				const Vector t_vec = t_vector(temp_t);
				const Vector t_magic = t_vec * magic;

				const double x = t_magic * x_vector;
				const double y = t_magic * y_vector;
				const double z = t_magic * z_vector;

				real.push_back(Point(x, y, z));
				temp_t += t;
			}

			temp_t = t;
		}

		// No need to waste space
		real.shrink_to_fit();
	}
};

#endif  // BEZIER_CURVE_H
