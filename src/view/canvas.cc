#include "canvas.h"

View::Canvas::Canvas() {}

View::Canvas::~Canvas() {}

bool View::Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);

	for (Drawable draw : queue) {
		draw_shape(cr, draw);
	}
	cr->stroke();

	return true;
}

void View::Canvas::draw_shape(
	const Cairo::RefPtr<Cairo::Context>& cr,
	const Drawable& draw) {


	std::vector<Point> points = draw.points;
	int total_points = points.size();

	// First point
	Point first_point = points[0];
	cr->move_to(first_point.x_coord, first_point.y_coord);

	// Lines to other points
	for (int i = 1; i < total_points; i++) {
		Point point = points[i];
		cr->line_to(point.x_coord, point.y_coord);
	}

	// Line from last point to first point
	cr->line_to(first_point.x_coord, first_point.y_coord);
}