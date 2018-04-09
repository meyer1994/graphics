#ifndef MODE_VIEWPORT_H
#define MODE_VIEWPORT_H

#include <vector>

#include <gtkmm/drawingarea.h>

#include "dot.h"
#include "line.h"
#include "shape.h"
#include "point.h"
#include "window.h"
#include "polygon.h"
#include "clipping.h"
#include "bezier_curve.h"

namespace Mode {

class Viewport {
public:
	Viewport(Mode::Window& window, std::vector<Shape*>& shapes, Gtk::DrawingArea& drawing_area)
	: window(window),
	  shapes(shapes),
	  clipping(),
	  drawing_area(drawing_area) {

		drawing_area
			.signal_draw()
			.connect(sigc::mem_fun(*this, &Viewport::on_draw));
	}

	virtual ~Viewport() {}

	/**
	 * @brief Sets the desired clipping method for lines.
	 *
	 * @details 0 (default) is Cohen-Sutherland algorithm;
	 *          1 is Liang-Barsky algorithm.
	 * If a different number is provided, it will be set to the default type.
	 *
	 * @param type Number of the desired algorithm to be used.
	 */
	void set_line_clipping_method(int type) {
		if (type != 0 || type != 1) {
			type = 0;
		}
		line_clipping_method = type;
	}

	void toggle_clipping() {
		clipping_toggle = !clipping_toggle;
	}

	void draw() {
		drawing_area.queue_draw();
	}

	Mode::Window& window;
	std::vector<Shape*>& shapes;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		// Paints background in white
		cr->set_source_rgb(1, 1, 1);
		cr->paint();

		// Transformation matrix
		Matrix m = window.normalization_matrix();

		// Change color to blue
		cr->set_source_rgb(0, 1, 1);

		// Draw clipping region for debugging
		window.window.clear();
		std::vector<Point> draw_points;
		for (Point p : window.real) {
			p.transform(m);
			window.window.push_back(p);

			p = vp_transform(p);
			draw_points.push_back(p);
		}
		window.draw(cr, draw_points);
		cr->stroke();

		// Changes color to red
		cr->set_source_rgb(0.8, 0, 0);

		// Draw all shapes
		for (Shape* s : shapes) {

			s->window.clear();

			// Normalize and transform to viewport
			for (Point p : s->real) {
				p.transform(m);
				s->window.push_back(p);
			}

			if (clipping_toggle) {
				clipper(s);
			}

			std::vector<Point> draw_points;
			for (Point p : s->window) {
				p = vp_transform(p);
				draw_points.push_back(p);
			}

			s->draw(cr, draw_points);

			if (dynamic_cast<Polygon*>(s) != nullptr) {
				Polygon* p = dynamic_cast<Polygon*>(s);
				if(p->filled == true) {
					cr->fill();
				}
			}
			cr->stroke();
		}

		return true;
	}

	Point vp_transform(const Point& p) {
		Gtk::Allocation alloc = drawing_area.get_allocation();
		double xvmax = alloc.get_width();
		double yvmax = alloc.get_height();

		double x = ((p[0] + 1) / 2) * (xvmax);
		double y = (1 - (p[1] + 1) / 2) * (yvmax);
		return Point(x, y);
	}

	void clipper(Shape* shape) {
		// Dot
		if (dynamic_cast<Dot*>(shape) != nullptr) {
			return clipping.dot(shape);
		}

		// Line
		if (dynamic_cast<Line*>(shape) != nullptr) {
			if (line_clipping_method == 0) {
				return clipping.cohen_sutherland(shape);
			}
			return clipping.liang_barsky(shape);
		}

		// Curve
		if (dynamic_cast<BezierCurve*>(shape) != nullptr) {
			return clipping.bezier_curve(shape);
		}

		// Polygon
		if (dynamic_cast<Polygon*>(shape) != nullptr) {
			return clipping.sutherland_hodgman(shape);
		}
	}

	Gtk::DrawingArea& drawing_area;
	Clipping clipping;
	int line_clipping_method = 0;
	bool clipping_toggle = true;
};

}  // namespace Mode

#endif  // MODE_VIEWPORT_H
