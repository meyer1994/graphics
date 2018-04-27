#ifndef CLIPPING_H
#define CLIPPING_H

#include <iostream>

#include "window.h"
#include "shapes/line.h"
#include "shapes/point.h"
#include "shapes/shape.h"
#include "shapes/vector.h"
#include "shapes/polygon.h"

const short INSIDE = 0;  // 0000
const short LEFT   = 1;  // 0001
const short RIGHT  = 2;  // 0010
const short BOTTOM = 4;  // 0100
const short TOP    = 8;  // 1000

class Clipping {
public:
	Clipping(Polygon& clip_region)
	: clip_region(clip_region),
	  xmax(0.9),
	  ymax(0.9),
	  xmin(-0.9),
	  ymin(-0.9) {
		if (clip_region.real.size() != 4) {
			throw std::invalid_argument("Clip region shape should be a rectangle. The sizes used will be the first point and the third point of it");
		}

		// Not used because the teacher wants to see the clipping working
		// xmax = clip_region[2][0];
		// ymax = clip_region[2][1];
		// xmin = clip_region[0][0];
		// ymin = clip_region[0][0];
	}

	virtual ~Clipping() {}

	void dot(Shape* dot) {
		Point& point = dot->window[0];

		bool x_inside = point[0] < -1 || point[0] > 1;
		bool y_inside = point[1] < -1 || point[1] > 1;

		if (!x_inside || !y_inside) {
			dot->window.clear();
		}
	}

	void curve(Shape* curve) {
		std::vector<Point> clipped;

		for (int i = 0; i < curve->window.size() - 1; i++) {
			Point a = curve->window[i];
			Point b = curve->window[i + 1];

			Point na = a;
			Point nb = b;
			bool result = cohen_sutherland_aux(na, nb);
			if (result) {
				clipped.push_back(na);

				if (nb != b) {
					clipped.push_back(nb);
				}
			}
		}

		curve->window = clipped;
	}

	void cohen_sutherland(Shape* line) {
		Point& a = line->window[0];
		Point& b = line->window[1];

		bool result = cohen_sutherland_aux(a, b);

		if (!result) {
			line->window.clear();
		}
	}

	bool cohen_sutherland_aux(Point& a, Point& b) {
		short a_code = out_code(a);
		short b_code = out_code(b);

		while(true) {
			// Trivial accept
			if ((a_code | b_code) == 0) {
				return true;
			}

			// Trivial reject
			if ((a_code & b_code) != 0) {
				return false;
			}

			// Find which point is outside viewport
			short out = a_code ? a_code : b_code;

			// Find intersection point
			double x;
			double y;
			if (out & TOP) {           // point is above the clip window
				x = a[0] + (b[0] - a[0]) * (ymax - a[1]) / (b[1] - a[1]);
				y = ymax;
			} else if (out & BOTTOM) { // point is below the clip window
				x = a[0] + (b[0] - a[0]) * (ymin - a[1]) / (b[1] - a[1]);
				y = ymin;
			} else if (out & RIGHT) {  // point is to the right of clip window
				y = a[1] + (b[1] - a[1]) * (xmax - a[0]) / (b[0] - a[0]);
				x = xmax;
			} else if (out & LEFT) {   // point is to the left of clip window
				y = a[1] + (b[1] - a[1]) * (xmin - a[0]) / (b[0] - a[0]);
				x = xmin;
			}

			// Move point to viewport edge
			if (out == a_code) {
				a[0] = x;
				a[1] = y;
				a_code = out_code(a);
			} else {
				b[0] = x;
				b[1] = y;
				b_code = out_code(b);
			}
		}
	}

	void liang_barsky(Shape* line) {
		Point& a = line->window[0];
		Point& b = line->window[1];

		double x1 = a[0];
		double y1 = a[1];

		double x2 = b[0];
		double y2 = b[1];

		// defining variables
		double p1 = -(x2 - x1);
		double p2 = -p1;
		double p3 = -(y2 - y1);
		double p4 = -p3;

		double q1 = x1 - xmin;
		double q2 = xmax - x1;
		double q3 = y1 - ymin;
		double q4 = ymax - y1;

		double posarr[5], negarr[5];
		int posind = 1, negind = 1;
		posarr[0] = 1;
		negarr[0] = 0;


		if ((p1 == 0 && q1 < 0) || (p3 == 0 && q3 < 0)) {
			line->window.clear();
			return;
		}

		if (p1 != 0) {
			double r1 = q1 / p1;
			double r2 = q2 / p2;
			if (p1 < 0) {
				negarr[negind++] = r1; // for negative p1, add it to negative array
				posarr[posind++] = r2; // and add p2 to positive array
			} else {
				negarr[negind++] = r2;
				posarr[posind++] = r1;
			}
		}

		if (p3 != 0) {
			double r3 = q3 / p3;
			double r4 = q4 / p4;
			if (p3 < 0) {
				negarr[negind++] = r3;
				posarr[posind++] = r4;
			} else {
				negarr[negind++] = r4;
				posarr[posind++] = r3;
			}
		}

		double xn1, yn1, xn2, yn2;
		double rn1, rn2;
		rn1 = max(negarr, negind); // maximum of negative array
		rn2 = min(posarr, posind); // minimum of positive array

		if (rn1 > rn2)  { // reject
			line->window.clear();
			return;
		}

		a[0] = x1 + p2 * rn1;
		a[1] = y1 + p4 * rn1; // computing new points

		b[0] = x1 + p2 * rn2;
		b[1] = y1 + p4 * rn2;
	}

	void sutherland_hodgman(Shape* polygon) {
		std::vector<Point> clp{
			Point(xmin, ymin),
			Point(xmax, ymin),
			Point(xmax, ymax),
			Point(xmin, ymax)
		};

		//i and k are two consecutive indexes
	   	for (int i = 0; i < clp.size(); i++) {
	      	int k = (i + 1) % clp.size();

	       	Point e0 = clp[i];
	       	Point e1 = clp[k];
	       	// We pass the current array of vertices, it's size
	       	// and the end points of the selected clipper line
	        clip(polygon->window, e0, e1);
	    }
	}

protected:
	// Window values (normalized)
	Polygon& clip_region;
	double xmax;
	double ymax;
	double xmin;
	double ymin;

	const short out_code(const Point& point) const {
		// Point values
		double x = point[0];
		double y = point[1];

		short code = INSIDE;

		if (x < xmin) {
			code |= LEFT;
		} else if (x > xmax) {
			code |= RIGHT;
		}

		if (y < ymin) {
			code |= BOTTOM;
		} else if (y > ymax) {
			code |= TOP;
		}

		return code;
	}

	double max(double v[], int n) {
		double max = v[0];
		for (int i = 0; i < n; i++) {
			if (v[i] > max) {
				max = v[i];
			}
		}
		return max;
	}

	double min(double v[], int n) {
		double min = v[0];
		for (int i = 0; i < n; i++) {
			if (v[i] < min) {
				min = v[i];
			}
		}
		return min;
	}

	void clip(std::vector<Point>& points, Point& e0, Point& e1) {
		std::vector<Point> new_points;
		double x1 = e0[0];
		double y1 = e0[1];
		double x2 = e1[0];
		double y2 = e1[1];

		for (int i = 0; i < points.size(); i++) {
			int k = (i + 1) % points.size();
			Point a = points[i];
			Point b = points[k];

			double ix = a[0];
			double iy = a[1];
			double kx = b[0];
			double ky = b[1];

			double i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
	        double k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);

	        // Case 1
			if (i_pos >= 0  && k_pos >= 0) {
	            //Only second point is added
	            new_points.push_back(Point(kx, ky));

	        // Case 2: When only first point is outside
	        } else if (i_pos < 0  && k_pos >= 0) {
	            // Point of intersection with edge
	            // and the second point is added
	            new_points.push_back(intersection(e0, e1, a, b));
	            new_points.push_back(Point(kx, ky));

	        // Case 3: When only second point is outside
	        } else if (i_pos >= 0  && k_pos < 0) {
	            //Only point of intersection with edge is added
	            new_points.push_back(intersection(e0, e1, a, b));

	        // Case 4: When both points are outside
	        } else {
	            //No points are added
	        }
	    }

	    // Copying new points into original array
	    // and changing the no. of vertices
	    if(new_points.size() == 0) {
	    	points.clear();
	    	points.push_back(Point(0,0));
	    } else {
	    points = new_points;
		}
	}

	Point intersection(Point& p1, Point& p2, Point& p3, Point& p4) {
		// Easier understanding
		double x1 = p1[0];
		double x2 = p2[0];
		double x3 = p3[0];
		double x4 = p4[0];

		double y1 = p1[1];
		double y2 = p2[1];
		double y3 = p3[1];
		double y4 = p4[1];

		// Results
		double x = 0;
		double y = 0;

		x  = (x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4);
		x /= (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

		y  = (x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4);
		y /= (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

		return Point(x, y);
	}
};

#endif  // CLIPPING_H
