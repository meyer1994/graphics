#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <gtkmm/drawingarea.h>
#include "../shapes/drawable.h"
#include "../shapes/point.h"
#include "../shapes/line.h"
#include "../shapes/polygon.h"

namespace View {

class Canvas : public Gtk::DrawingArea {
public:
	Canvas() {}
    
	~Canvas() {}

	std::vector<Drawable> queue;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        Shape::Point p(10.0, 10.0);
        Shape::Line l(Coordinate {10.0, 20.0}, Coordinate {40.0, 20.0});
        Shape::Polygon r(std::vector<Coordinate> {
            Coordinate {10.0, 30.0},
            Coordinate {40.0, 30.0},
            Coordinate {40.0, 60.0},
            Coordinate {10.0, 60.0}
        });

        queue.push_back(p);
        queue.push_back(l);
        queue.push_back(r);

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

        std::vector<Coordinate> points = draw.points;
        int total_points = points.size();

        // First point
        Coordinate first_point = points[0];
        cr->move_to(first_point.x, first_point.y);

        // Lines to other points
        for (int i = 1; i < total_points; i++) {
            Coordinate point = points[i];
            cr->line_to(point.x, point.y);
        }

        // Line from last point to first point
        cr->line_to(first_point.x, first_point.y);
    }

};

}  // namespace View

#endif  // CANVAS_H