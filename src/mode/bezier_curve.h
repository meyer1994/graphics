#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "point.h"
#include "shape.h"

class BezierCurve : public Shape {
public:
	BezierCurve() : Shape(name = "curve") {}

	BezierCurve(std::vector<Point> points, double t = 0.05, std::string name = "curve")
	: Shape(points, name),
	  input(points),
	  t(t) {
		if (points.size() % 3 != 1) {
			throw std::invalid_argument("Points size must obey { size % 3 == 1"
										" }");
		}

		blending_function();
	}

	~BezierCurve() {}

    const Type type = Type::BezierCurve;

	std::vector<Point> input;
	double t;
	const Matrix magic{
		Vector{-1,  3, -3, 1},
		Vector{ 3, -6,  3, 0},
		Vector{-3,  3,  0, 0},
		Vector{ 1,  0,  0, 0}
	};

protected:
	Vector get_t_vector(double tee) {
		return Vector{
			tee * tee * tee,
			tee * tee,
			tee,
			1
		};
	}

	void blending_function() {
		double temp_t = t;
		real.clear();

		for (int i = 0; i < input.size() - 1; i += 3) {
			// Get points
			Point p0 = input[i];
			Point p1 = input[i + 1];
			Point p2 = input[i + 2];
			Point p3 = input[i + 3];

			Vector x_vector{
				p0[0],
				p1[0],
				p2[0],
				p3[0]
			};
			Vector y_vector{
				p0[1],
				p1[1],
				p2[1],
				p3[1]
			};

			while (temp_t <= 1) {
				Vector t_vector = get_t_vector(temp_t);
				Vector t_magic = Transformation::multiply(t_vector, magic);

				double x = Transformation::multiply(t_magic, x_vector);
				double y = Transformation::multiply(t_magic, y_vector);

				std::cout << x << "\n" << y << "\n\n";

				real.push_back(Point(x, y));

				temp_t += t;
			}

			temp_t = t;
		}
	}
};

#endif  // BEZIER_CURVE_H
