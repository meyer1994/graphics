#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <gtkmm/drawingarea.h>
#include "../shapes/drawable.h"

namespace View {

class Canvas : public Gtk::DrawingArea {
public:
	Canvas() {}
    
	~Canvas() {}

	std::vector<Drawable> queue;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        for (Drawable draw : queue) {
            draw_shape(cr, draw);
        }
        cr->stroke();

        return true;
    }

private:
	void draw_shape(
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

};

}  // namespace View

#endif  // CANVAS_H