#ifndef MODE_VIEWPORT_H
#define MODE_VIEWPORT_H

#include <vector>

#include <gtkmm/drawingarea.h>

#include "point.h"
#include "shape.h"
#include "window.h"
#include "clipping.h"

namespace Mode {

class Viewport {
public:
	Viewport(Mode::Window& window, std::vector<Shape>& shapes, Gtk::DrawingArea& drawing_area)
	: window(window),
	  shapes(shapes),
	  clipping(),
	  drawing_area(drawing_area) {

		drawing_area
			.signal_draw()
			.connect(sigc::mem_fun(*this, &Viewport::on_draw));
	}

	~Viewport() {}

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
	std::vector<Shape>& shapes;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		// Configuration for dots to appear when drawn
		cr->set_line_cap(Cairo::LINE_CAP_ROUND);

		// Paints background in white
		cr->set_source_rgb(1, 1, 1);
		cr->paint();

		// Transformation matrix
		Matrix m = window.normalization_matrix();

		// Change color to blue
		cr->set_source_rgb(0, 1, 1);
		normalize_shape(window, m);
		draw_shape(cr, window.window);
		cr->stroke();

		// Changes color to red
		cr->set_source_rgb(0.8, 0, 0);

		// Draw all shapes
		for (Shape s : shapes) {
			normalize_shape(s, m);

			if (clipping_toggle) {
				clipper(s);
			}

			draw_shape(cr, s.window);
		}
		cr->stroke();

		return true;
	}

	void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, std::vector<Point>& points) {
		if (points.empty()) {
			return;
		}

		// First point
		Point p0 = points[0];

		Point p0v = vp_transform(p0);
		cr->move_to(p0v[0], p0v[1]);

		// Lines to other points
		for (Point point : points) {
			Point n = vp_transform(point);
			cr->line_to(n[0], n[1]);
		}

		// Line from last point to first point
		cr->line_to(p0v[0], p0v[1]);
	}

	void normalize_shape(Shape& shape, Matrix& transformation) {
		shape.window.clear();
		for (Point p : shape.real) {
			p.transform(transformation);
			shape.window.push_back(p);
		}
	}

	Point vp_transform(const Point& p) {
		Gtk::Allocation alloc = drawing_area.get_allocation();
		double xvmax = alloc.get_width();
		double yvmax = alloc.get_height();

		double x = ((p[0] + 1) / 2) * (xvmax);
		double y = (1 - (p[1] + 1) / 2) * (yvmax);
		return Point(x, y);
	}

	void clipper(Shape& shape) {
		// Dot
		if (shape.size() == 1) {
			return clipping.dot(shape);
		}

		// Line
		if (shape.size() == 2) {
			if (line_clipping_method == 0) {
				return clipping.cohen_sutherland(shape);
			}

			return clipping.liang_barsky(shape);
		}

		// Polygon
		clipping.sutherland_hodgman(shape);
	}

	Gtk::DrawingArea& drawing_area;
	Clipping clipping;
	int line_clipping_method = 0;
	bool clipping_toggle = true;
};
	
}  // namespace Mode

#endif  // MODE_VIEWPORT_H