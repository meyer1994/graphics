#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <vector>
#include <string>
#include <stdexcept>

#include <cairomm/context.h>

#include "point.h"
#include "shape.h"

class BezierCurve : public Shape {
public:
	BezierCurve() : Shape("bezier_curve") {}

	BezierCurve(std::string name) : Shape(name) {}

	BezierCurve(std::vector<Point> points, double t = 0.05, std::string name = "curve")
	: Shape(points, name),
	  input(points),
	  t(t) {
		if (points.size() % 3 != 1) {
			throw std::invalid_argument("Points size must obey { size % 3 == 1 }");
		}

		blending_function();
	}

	virtual ~BezierCurve() {}

	virtual const std::string to_string() const override {
		if (input.empty()) {
			return std::string("BezierCurve()");
		}

		std::string str = "BezierCurve(";

		for (int i = 0; i < input.size() - 1; i++) {
			const Point& p = input[i];
			str += p.to_string() + ", ";
		}

		str += input.back().to_string() + ")";

		return str;
	}

	virtual void draw(
		const Cairo::RefPtr<Cairo::Context>& cr,
        const std::vector<Point>& points) const override {

		const Point& first = points.front();
		cr->move_to(first[0], first[1]);

		for (int i = 1; i < points.size(); i++) {
			const Point& p = points[i];
			cr->line_to(p[0], p[1]);
		}
	}

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

				// std::cout << x << "\n" << y << "\n\n";

				real.push_back(Point(x, y));

				temp_t += t;
			}

			temp_t = t;
		}
	}
};

#endif  // BEZIER_CURVE_H
