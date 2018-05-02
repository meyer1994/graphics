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
	Viewport(Window& window, std::vector<BaseShape*>& shapes, Gtk::DrawingArea& drawing_area)
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

	void toggle_clipping() {
		clipping_active = !clipping_active;
	}

	void draw() {
		drawing_area.queue_draw();
	}

	Clipping clipping;
	Window& window;
	std::vector<BaseShape*>& shapes;

protected:
	bool clipping_active = true;
	Gtk::DrawingArea& drawing_area;

	const bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
		// Paints background in white
		cr->set_source_rgb(1, 1, 1);
		cr->paint();

		// Set pen style
		cr->set_line_cap(Cairo::LINE_CAP_ROUND);

		// Changes color to red
		cr->set_source_rgb(0.8, 0, 0);

		// Parallel projection matrix
		const Matrix m = window.projection_matrix();

		// Draw all shapes
		for (BaseShape* shape : shapes) {

			// Project it
			shape->w_transform(m);

			// Clip it
			if (clipping_active) {
				clipping.clip_it(shape);
			}

			// Draw it
			draw_it(cr, shape);

			// Stroke it ( ͡° ͜ʖ ͡°)
			cr->stroke();
		}

		// Change color to blue
		cr->set_source_rgb(0, 1, 1);
		draw_it(cr, &window);
		cr->stroke();

		return true;
	}

	void draw_it(const Cairo::RefPtr<Cairo::Context>& cr, BaseShape* s) {
		// Polyhedron
		if (s->type() == ShapeType::Polyhedron) {
			draw_polyhedron(cr, s);
		}

		// Everything else
		draw_shape(cr, s);
	}

	void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, BaseShape* s) {
		Shape* shape = dynamic_cast<Shape*>(s);
		if (shape == nullptr) {
			return;
		}

		// Move pen to first point
		const Point first = vp_transform(shape->window.front());
		cr->move_to(first[0], first[1]);

		// Draw all other points
		for (const Point& p : shape->window) {
			const Point t = vp_transform(p);
			cr->line_to(t[0], t[1]);
		}

		// Polygon, close drawing
		if (shape->type() == ShapeType::Polygon) {
			cr->close_path();
		}

		// Fill it
		if (shape->filled) {
			cr->fill();
		}
	}

	void draw_polyhedron(const Cairo::RefPtr<Cairo::Context>& cr, BaseShape* s) {
		Polyhedron* poly = dynamic_cast<Polyhedron*>(s);
		if (poly == nullptr) {
			return;
		}

		for (Polygon& p : poly->faces) {
			draw_shape(cr, &p);
		}
	}

	const Point vp_transform(const Point& p) {
		const Gtk::Allocation alloc = drawing_area.get_allocation();
		const double xvmax = alloc.get_width();
		const double yvmax = alloc.get_height();

		const double x = ((p[0] + 1) / 2) * (xvmax);
		const double y = (1 - (p[1] + 1) / 2) * (yvmax);
		return Point(x, y);
	}
};

}  // namespace Mode

#endif  // MODE_VIEWPORT_H
