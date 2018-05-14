#ifndef SURFACE_BEZIER_H
#define SURFACE_BEZIER_H

#include <string>
#include <vector>
#include <initializer_list>

#include "point.h"
#include "base_shape.h"


class SurfaceBezier : public Shape {
public:
	SurfaceBezier() : Shape("surfacebezier") {}

	SurfaceBezier(std::initializer_list<std::vector<Point>> d)
	: SurfaceBezier(std::vector<std::vector<Point>>(d)) {}

	SurfaceBezier(std::vector<std::vector<Point>> v, double t = 0.05, std::string name = "surfacebezier")
	: Shape(name) {
		blending_function(v);
		calculate_medium();
	}

	virtual ~SurfaceBezier() {

	}

	virtual const std::string to_string() const override {
		return "";
	}

	virtual const ShapeType type() const override {
		return ShapeType::BezierSurface;
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

	const Vector t_vector_t(const double tee) {
		return Vector{
			1,
			tee,
			tee * tee,
			tee * tee * tee
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
		for (int i = 0; i < v.size() - 1; i += 3) {
			for (int j = 0; j < v[i].size() - 1; j += 3) {
				// Matrix
				Matrix x_matrx = x_matrix(i, j, v);
				Matrix y_matrx = y_matrix(i, j, v);
				Matrix z_matrx = z_matrix(i, j, v);

				// S
				for (double temp_s = t; temp_s <= 1; temp_s += t) {
					const Vector s_magic = t_vector(temp_s) * magic;

					// T
					for (double temp_t = t; temp_t <= 1; temp_t += t) {
						const Vector t_magic = magic * t_vector(temp_t);

						const double x = s_magic * x_matrx * t_magic;
						const double y = s_magic * y_matrx * t_magic;
						const double z = s_magic * z_matrx * t_magic;

						real.push_back(Point(x, y, z));
						
					}
				}
				
				transpose(x_matrx);
				transpose(y_matrx);
				transpose(z_matrx);

				// S
				for (double temp_s = t; temp_s <= 1; temp_s += t) {
					const Vector s_magic = t_vector(temp_s) * magic;

					// T
					for (double temp_t = t; temp_t <= 1; temp_t += t) {
						const Vector t_magic = magic * t_vector(temp_t);

						const double x = s_magic * x_matrx * t_magic;
						const double y = s_magic * y_matrx * t_magic;
						const double z = s_magic * z_matrx * t_magic;

						real.push_back(Point(x, y, z));
						
					}
				}
			}
		}
	}

		/* =========================================== */
	void transpose(Matrix& matr)
	/* =========================================== */
	{
	  Matrix result = {
	  	{0,0,0,0},
	  	{0,0,0,0},
	  	{0,0,0,0},
	  	{0,0,0,0}
		};
	  for (int i = 0; i<4; i++)
	    {
	    for (int j=0; j<4; j++)
	      {
	         result[i][j] = matr[j][i];
	      }
	    }
	  for (int i = 0; i<4; i++)
	    {
	    for (int j=0; j<4; j++)
	      {
	         matr[i][j] = result[i][j];
	      }
	  }
	}
};

#endif  // SURFACE_BEZIER_H
