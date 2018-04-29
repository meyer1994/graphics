#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>

#include "point.h"
#include "shape.h"

class Spline : public Shape {
public:
	Spline() : Shape("spline") {}

	Spline(std::string name) : Shape(name) {}

	Spline(std::initializer_list<Point> d)
	: Shape(d, "spline") {
		if (real.size() < 4) {
			throw std::invalid_argument("Points size must bigger than 3");
		}

		blending_function(std::vector<Point>(d));
	}

	Spline(std::vector<Point> points, double t, std::string name = "spline")
	: Shape(points, name),
	  t(t) {
		if (points.size() < 4) {
			throw std::invalid_argument("Points size must bigger than 3");
		}

		blending_function(points);
	  }

	virtual ~Spline() {}

	const std::string to_string() const override {
		if (real.empty()) {
			return std::string("Spline()");
		}

		std::string str = "Spline(";
		for (int i = 0 ; i < real.size() - 1; i++) {
			const Point& p = real[i];
			str += p.to_string() + ", ";
		}
		const Point& last = real.back();
		str += last.to_string() + ")";
		return str;
	}

	const ShapeType type() const override {
		return ShapeType::Spline;
	}

	double t = 0.1;

protected:
	const Matrix magic{
		Vector{-1.0/6.0,  1.0/2.0, -1.0/2.0, 1.0/6.0},
		Vector{ 1.0/2.0, -1.0,      1.0/2.0, 0},
		Vector{-1.0/2.0,  0.0,      1.0/2.0, 0},
		Vector{ 1.0/6.0,  2.0/3.0,  1.0/6.0, 0}
	};

	const Matrix t_matrix(const double tee) {
		return Matrix{
			Vector{0, 0, 0, 1},
			Vector{tee * tee * tee, tee * tee, tee, 0},
			Vector{6 * tee * tee * tee, 2 * tee * tee, 0, 0},
			Vector{6 * tee * tee * tee, 0, 0, 0}
		};
	}

	void blending_function(const std::vector<Point> v) {
		real.clear();

		for (int i = 0; i + 3 < v.size(); i++) {
			// Get points
			const Point& p0 = v[i];
			const Point& p1 = v[i + 1];
			const Point& p2 = v[i + 2];
			const Point& p3 = v[i + 3];

			const Vector gx{p0[0], p1[0], p2[0], p3[0]};
			const Vector gy{p0[1], p1[1], p2[1], p3[1]};

			const Matrix t_mat = t_matrix(t);

			const Vector cx = magic * gx;
			const Vector cy = magic * gy;

			const Vector fwdx = t_mat * cx;
			const Vector fwdy = t_mat * cy;

			fwd_diff(fwdx, fwdy);
		}

		real.shrink_to_fit();
	}

	void fwd_diff(const Vector& fwdx, const Vector& fwdy) {
		int n = 1 / t;

		double x   = fwdx[0];
		double dx  = fwdx[1];
		double d2x = fwdx[2];
		double d3x = fwdx[3];
		double y   = fwdy[0];
		double dy  = fwdy[1];
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
