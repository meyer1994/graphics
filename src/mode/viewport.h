#ifndef MODE_VIEWPORT_H
#define MODE_VIEWPORT_H

#include <vector>

#include <gtkmm/drawingarea.h>

#include "window.h"
#include "clipping.h"
#include "shapes/dot.h"
#include "shapes/line.h"
#include "shapes/shape.h"
#include "shapes/point.h"
#include "shapes/polygon.h"
#include "shapes/bezier_curve.h"

namespace Mode {

class Viewport {
public:
	Viewport(Mode::Window& window, std::vector<Shape*>& shapes, Gtk::DrawingArea& drawing_area)
	: window(window),
	  shapes(shapes),
	  clipping(window),
	  drawing_area(drawing_area) {

	  	// Connect
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
		if (type != COHEN_SUTHERLAND || type != LIANG_BARSKY) {
			type = COHEN_SUTHERLAND;
			return;
		}
		line_clipping_method = type;
	}

	void toggle_clipping() {
		clipping_active = !clipping_active;
	}

	void draw() {
		drawing_area.queue_draw();
	}

	Mode::Window& window;
	std::vector<Shape*>& shapes;

	static const int COHEN_SUTHERLAND = 0;
	static const int LIANG_BARSKY = 1;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		// Paints background in white
		cr->set_source_rgb(1, 1, 1);
		cr->paint();

		// Parallel projection matrix
		const Matrix m = window.parallel_matrix();

		// Changes color to red
		cr->set_source_rgb(0.8, 0, 0);

		// Draw all shapes
		for (Shape* shape : shapes) {

			// Copy real points to window
			shape->window = shape->real;

			// Normalize points
			shape->w_transform(m);

			// Clipping
			if (clipping_active) {
				clipper(shape);
			}

			// Draw it
			if (!shape->window.empty()) {
				draw_shape_2d(cr, shape);
			}
			cr->stroke();
		}

		// Change color to blue
		cr->set_source_rgb(0, 1, 1);

		window.window = {
			{-0.9, -0.9, 0},
			{ 0.9, -0.9, 0},
			{ 0.9,  0.9, 0},
			{-0.9,  0.9, 0}
		};
		draw_shape_2d(cr, &window);
		cr->stroke();

		return true;
	}

	void draw_shape_2d(const Cairo::RefPtr<Cairo::Context>& cr, const Shape* shape) {
		// Dot case
		if (shape->type() == Type2D::Dot) {
			const Point& p = shape->window.front();
			const Cairo::LineCap cap = cr->get_line_cap();
			cr->set_line_cap(Cairo::LINE_CAP_ROUND);
			cr->move_to(p[0], p[1]);
			cr->line_to(p[0], p[1]);
			cr->set_line_cap(cap);
			return;
		}

		// Move pen to first point
		const Point& first = vp_transform(shape->window.front());
		cr->move_to(first[0], first[1]);

		// Draw all other points
		for (const Point& p : shape->window) {
			const Point t = vp_transform(p);
			cr->line_to(t[0], t[1]);
		}

		// Polygon, close drawing
		if (shape->type() == Type2D::Polygon) {
			cr->close_path();

			// Fill it
			if (shape->filled) {
				cr->fill();
			}
		}
	}

	const Point vp_transform(const Point& p) {
		Gtk::Allocation alloc = drawing_area.get_allocation();
		const double xvmax = alloc.get_width();
		const double yvmax = alloc.get_height();

		const double x = ((p[0] + 1) / 2) * (xvmax);
		const double y = (1 - (p[1] + 1) / 2) * (yvmax);
		return Point(x, y);
	}

	void clipper(Shape* shape) {
		Type2D type = shape->type();
		switch(type) {
			case Type2D::Dot:
				return clipping.dot(shape);

			case Type2D::Line:
			{
				if (line_clipping_method == 0) {
					return clipping.cohen_sutherland(shape);
				}
				return clipping.liang_barsky(shape);
			}

			case Type2D::BezierCurve:
			case Type2D::Spline:
				return clipping.curve(shape);

			default:
				return clipping.sutherland_hodgman(shape);
		}
	}

	Gtk::DrawingArea& drawing_area;
	Clipping clipping;
	int line_clipping_method = 0;
	bool clipping_active = true;
};

}  // namespace Mode

#endif  // MODE_VIEWPORT_H
