#ifndef SURFACE_SPLINE_H
#define SURFACE_SPLINE_H


#include <string>
#include <stdexcept>
#include <vector>
#include <initializer_list>

#include "point.h"
#include "shape_complex.h"
#include "spline.h"


class SurfaceSpline : public ShapeComplex {
public:
	SurfaceSpline() : ShapeComplex("SurfaceSpline") {}

	SurfaceSpline(std::initializer_list<std::vector<Point>> d)
	: SurfaceSpline(std::vector<std::vector<Point>>(d)) {}

	SurfaceSpline(std::vector<std::vector<Point>> v, double t = 0.05, std::string name = "SurfaceSpline")
	: ShapeComplex(name) {
		if(v.size() < 4) {
			throw std::invalid_argument("Points size must bigger than 3");
		}
		blending_function(v);
		calculate_medium();
	}

	virtual ~SurfaceSpline() {

	}

	virtual const std::string to_string() const override {
		return "";
	}

	virtual const ShapeType type() const override {
		return ShapeType::SplineSurface;
	}

	double t = 0.05;

protected:
	// b-Spline Method Matrix (can use Bezier, Hermit...)
	const Matrix magic{
		Vector{-1.0/6.0,  1.0/2.0, -1.0/2.0, 1.0/6.0},
		Vector{ 1.0/2.0, -1.0,      1.0/2.0, 0},
		Vector{-1.0/2.0,  0.0,      1.0/2.0, 0},
		Vector{ 1.0/6.0,  2.0/3.0,  1.0/6.0, 0}
	};

	// t_matrix = Delta s = delta_s = Es
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

	// t_matrix_t = Delta t = delta_t = Et
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

	// Geometry Matrix = Ax, Ay, Az
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

	// Ax
	const Matrix x_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 0);
	}

	// Ay
	const Matrix y_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 1);
	}

	// Az
	const Matrix z_matrix(
		const int i,
		const int j,
		const std::vector<std::vector<Point>>& v)
	{
		return g_matrix(i, j, v, 2);
	}

	// calculateCoefficients to store in Cofficients Matrix
		// <method matrix> * <geometry matrix> * <method matrix>
		// <magic matrix>  * <g_matrix> 	   * <magic matrix>
	void blending_function(const std::vector<std::vector<Point>>& v) {
		int n = 1/t;
		for (int i = 0; i + 3 < v.size(); i++) {
			for (int j = 0; j + 3 < v[i].size(); j++) {
				// Matrix
				const Matrix Ax = x_matrix(i, j, v);
				const Matrix Ay = y_matrix(i, j, v);
				const Matrix Az = z_matrix(i, j, v);

				const Matrix Cx = magic * Ax * magic;
				const Matrix Cy = magic * Ay * magic;
				const Matrix Cz = magic * Az * magic;

				// creating t_matrix and t_matrix_t
				const Matrix Es = t_matrix(t);    // Et
				const Matrix Et = t_matrix_t(t);  // Es

				// creating forward diff matrices (DD)
					// <Es> 	  * <Cx> * <Et>
					// <t_matrix> * <Cx> * <t_matrix_t>
				Matrix DDx = Es * Cx * Et;
				Matrix DDy = Es * Cy * Et;
				Matrix DDz = Es * Cz * Et;

				for (int s = 0; s < n; s += 1) {
					fwd_diff(DDx, DDy, DDz);
					updateFwdDiffMatrices(DDx);
					updateFwdDiffMatrices(DDy);
					updateFwdDiffMatrices(DDz);
				}

				// creating forward diff matrices (DD)
					// <Es> 	  * <Cx> * <Et>
					// <t_matrix> * <Cx> * <t_matrix_t>
				DDx = Es * Cx * Et;
				DDy = Es * Cy * Et;
				DDz = Es * Cz * Et;				

				transpose(DDx);
				transpose(DDy);
				transpose(DDz);

				for (int s = 0; s < n; s += 1) {
					fwd_diff(DDx, DDy, DDz);
					updateFwdDiffMatrices(DDx);
					updateFwdDiffMatrices(DDy);
					updateFwdDiffMatrices(DDz);
				}				

				// int n = 1 / t;
				// for (double s = t; s < 1; s += t) {
				// 	Matrix cx = t_matrix(s) * x_matrx * t_matrix_t(t);
				// 	Matrix cy = t_matrix(s) * y_matrx * t_matrix_t(t);
				// 	Matrix cz = t_matrix(s) * z_matrx * t_matrix_t(t);
				// fwd_diff(cx[0], cy[0], cz[0]);
				//}
				
			}
		}
	}

	void fwd_diff(const Matrix& fwdx, const Matrix& fwdy, const Matrix& fwdz) {
		int n = 1 / t;

		double x   = fwdx[0][0];
		double Dx  = fwdx[0][1];
		double D2x = fwdx[0][2];
		double D3x = fwdx[0][3];
		double y   = fwdy[0][0];
		double Dy  = fwdy[0][1];
		double D2y = fwdy[0][2];
		double D3y = fwdy[0][3];
		double z   = fwdz[0][0];
		double Dz  = fwdz[0][1];
		double D2z = fwdz[0][2];
		double D3z = fwdz[0][3];

		Spline* scurve = new Spline();

		scurve->real.push_back(Point(x, y, z));

		double oldx, oldy, oldz;
		oldx = x;
		oldy = y;
		oldz = z;

		for (int i = 1; i < n; i++) {
		  	x = x + Dx;  Dx = Dx + D2x;  D2x = D2x + D3x;
		  	y = y + Dy;  Dy = Dy + D2y;  D2y = D2y + D3y;
		  	z = z + Dz;  Dz = Dz + D2z;  D2z = D2z + D3z;
		  	oldx = x;
		  	oldy = y;
		  	oldz = z;    
	  
			scurve->real.push_back(Point(x, y, z));
		}
		faces.push_back(scurve);
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

	void updateFwdDiffMatrices(Matrix& DDw)
	{
		for(int i = 0; i < 3; i++){
			int k = i+1;
			DDw[i] = DDw[i] + DDw[k];
		}
	}
};


#endif  // SURFACE_SPLINE_H
