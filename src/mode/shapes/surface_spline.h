#ifndef SURFACE_SPLINE_H
#define SURFACE_SPLINE_H


#include <string>
#include <vector>
#include <initializer_list>

#include "point.h"
#include "base_shape.h"


class SurfaceSpline : public Shape {
public:
	SurfaceSpline() : Shape("SurfaceSpline") {}

	SurfaceSpline(std::initializer_list<std::vector<Point>> d)
	: SurfaceSpline(std::vector<std::vector<Point>>(d)) {}

	SurfaceSpline(std::vector<std::vector<Point>> v, double t = 0.2, std::string name = "SurfaceSpline")
	: Shape(name) {
		blending_function(v);
		calculate_medium();
	}

	virtual ~SurfaceSpline() {

	}

	virtual const std::string to_string() const override {
		return "";
	}

	virtual const ShapeType type() const override {
		return ShapeType::BezierSurface;
	}

	double t = 0.2;

protected:
	const Matrix magic{
		Vector{-1.0/6.0,  1.0/2.0, -1.0/2.0, 1.0/6.0},
		Vector{ 1.0/2.0, -1.0,      1.0/2.0, 0},
		Vector{-1.0/2.0,  0.0,      1.0/2.0, 0},
		Vector{ 1.0/6.0,  2.0/3.0,  1.0/6.0, 0}
	};

	const Matrix t_matrix(const double tee) {
		const double t3 = tee * tee * tee;
		const double t2 = tee * tee;
		const double t1 = tee;
		return Matrix{
			Vector{   0,    0,  0, 1},
			Vector{  t3,   t2, t1, 0},
			Vector{6*t3, 2*t2,  0, 0},
			Vector{6*t3,    0,  0, 0}
		};
	}

	const Matrix t_matrix_t(const double tee) {
		const double t3 = tee * tee * tee;
		const double t2 = tee * tee;
		const double t1 = tee;
		return Matrix{
			Vector{0, t3, 6*t3, 6*t3},
			Vector{0, t2, 2*t2,    0},
			Vector{0, t1,    0,    0},
			Vector{1,  0,    0,    0}
		};
	}

	const Matrix g_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v,
		const int c)
	{
		// Creates 4x4 matrix
		Matrix matrix(4, Vector(4, 0));

		// Fill it up
		for (int k = i; k <= i + 3; k++) {
			for (int l = i; l <= i + 3; l++) {
				matrix[k][l] = v[k][l][c];
			}
		}

		return matrix;
	}

	const Matrix x_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 0);
	}

	const Matrix y_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 1);
	}

	const Matrix z_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 2);
	}

	void blending_function(const std::vector<std::vector<Point>>& v) {
		for (int i = 0; i + 3 < v.size(); i++) {
			for (int j = 0; j + 3 < v[i].size(); j++) {
				// Matrix
				const Matrix x_matrx = x_matrix(i, j, v);
				const Matrix y_matrx = y_matrix(i, j, v);
				const Matrix z_matrx = z_matrix(i, j, v);


				int n = 1 / t;

				for (double s = t; s < 1; s += t) {
					Matrix cx = t_matrix(s) * x_matrx * t_matrix_t(t);
					Matrix cy = t_matrix(s) * y_matrx * t_matrix_t(t);
					Matrix cz = t_matrix(s) * z_matrx * t_matrix_t(t);

					fwd_diff(cx[0], cy[0], cz[0]);
				}
			}
		}
	}

	void fwd_diff(const Matrix& fwdx, const Matrix& fwdy, const Matrix& fwdz) {
		int n = 1 / t;

		double x   = fwdx[0][0];
		double dx  = fwdx[0][1];
		double d2x = fwdx[0][2];
		double d3x = fwdx[0][3];
		double y   = fwdy[0][0];
		double dy  = fwdy[0][1];
		double d2y = fwdy[0][2];
		double d3y = fwdy[0][3];
		double z   = fwdz[0][0];
		double dz  = fwdz[0][1];
		double d2z = fwdz[0][2];
		double d3z = fwdz[0][3];

		real.push_back(Point(x, y, z));

		for (int i = 0; i < n; i++) {
			x += dx;
			dx += d2x;
			d2x += d3x;

			y += dy;
			dy += d2y;
			d2y += d3y;

			z += dz;
			dz += d2z;
			d2z += d3z;

			real.push_back(Point(x, y, z));
		}
	}
};


#endif  // SURFACE_SPLINE_H
