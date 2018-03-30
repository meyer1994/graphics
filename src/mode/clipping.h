#ifndef CLIPPING_H
#define CLIPPING_H

#include "line.h"
#include "point.h"
#include "shape.h"
#include "window.h"

const short INSIDE = 0; // 0000
const short LEFT = 1;   // 0001
const short RIGHT = 2;  // 0010
const short BOTTOM = 4; // 0100
const short TOP = 8;    // 1000

class Clipping {
public:
	Clipping() {}

	~Clipping() {}

	void cohen_sutherland(Shape& line) {

		Point& a = line.window[0];
		Point& b = line.window[1];

		short a_code = out_code(a);
		short b_code = out_code(b);

		while(true) {
			// Trivial accept
			if ((a_code | b_code) == 0) {
				return;
			}

			// Trivial reject
			if ((a_code & b_code) != 0) {
				line.window.clear();
				return;
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

	void liang_barsky(Shape& line) {
		Point& a = line.window[0];
		Point& b = line.window[1];

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
			line.window.clear();
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
			line.window.clear();
			return;
		}

		a[0] = x1 + p2 * rn1;
		a[1] = y1 + p4 * rn1; // computing new points

		b[0] = x1 + p2 * rn2;
		b[1] = y1 + p4 * rn2;
	}

protected:

	// Window values (normalized)
	double xmax = .9;
	double ymax = .9;
	double xmin = -.9;
	double ymin = -.9;

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
};

#endif  // CLIPPING_H
