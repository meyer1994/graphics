#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <string>

#include "shape.h"

class Spline : public Shape {
public:
	Spline() : Shape("spline") {}

	Spline(std::string name) : Shape(name) {}

	Spline(std::vector<Point> points, double t = 0.1, std::string name = "spline")
	: Shape(points, name),
	  input(points),
	  t(t) {

		if (points.size() < 4) {
			throw std::invalid_argument("Points size must bigger than 3");
		}

		blending_function();
	  }

	~Spline() {}

	const std::string to_string() const override {
		if (input.empty()) {
			return std::string("Spline()");
		}

		std::string str = "Spline(";
		for (int i = 0 ; i < input.size() - 1; i++) {
			str += input[i].to_string() + ", ";
		}
		str += input.back().to_string() + ")";
		return str;
	}

	const Type2D type() const override {
		return Type2D::Spline;
	}

	std::vector<Point> input;

protected:

	double t = 0.1;

	const Matrix magic{
		Vector{-1.0/6.0,  1.0/2.0, -1.0/2.0, 1.0/6.0},
		Vector{ 1.0/2.0, -1.0,      1.0/2.0, 0},
		Vector{-1.0/2.0,  0.0,      1.0/2.0, 0},
		Vector{ 1.0/6.0,  2.0/3.0,  1.0/6.0, 0}
	};

	Matrix get_t_matrix(double tee) {
		return Matrix{
			Vector{0, 0, 0, 1},
			Vector{tee * tee * tee, tee * tee, tee, 0},
			Vector{6 * tee * tee * tee, 2 * tee * tee, 0, 0},
			Vector{6 * tee * tee * tee, 0, 0, 0}
		};
	}

	void blending_function() {
		real.clear();

		for (int i = 0; i + 3 < input.size(); i++) {
			// Get points
			Point p0 = input[i];
			Point p1 = input[i + 1];
			Point p2 = input[i + 2];
			Point p3 = input[i + 3];

			Vector gx{
				p0[0],
				p1[0],
				p2[0],
				p3[0]
			};
			Vector gy{
				p0[1],
				p1[1],
				p2[1],
				p3[1]
			};

			Matrix t_matrix = get_t_matrix(t);

			Vector cx = Transformation::multiply(magic, gx);
			Vector cy = Transformation::multiply(magic, gy);

			Vector fwdx = Transformation::multiply(t_matrix, cx);
			Vector fwdy = Transformation::multiply(t_matrix, cy);

			fwd_diff(fwdx, fwdy);
		}
	}

	void fwd_diff(Vector& fwdx, Vector& fwdy) {
		int n = 1 / t;

		double x = fwdx[0];
		double dx = fwdx[1];
		double d2x = fwdx[2];
		double d3x = fwdx[3];
		double y = fwdy[0];
		double dy = fwdy[1];
		double d2y = fwdy[2];
		double d3y = fwdy[3];

		real.push_back(Point(x, y));

		for (int i = 0; i < n; i++) {
			x += dx;
			dx += d2x;
			d2x += d3x;

			y += dy;
			dy += d2y;
			d2y += d3y;

			real.push_back(Point(x, y));
		}
	}
};


#endif  // SPLINE_H
