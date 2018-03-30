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
};

#endif  // CLIPPING_H
