#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <gtkmm/drawingarea.h>
#include "../mode/drawable.h"
#include "../mode/point.h"

namespace View {

class Canvas : public Gtk::DrawingArea {
public:
    Canvas() : root{0, 0}, step_size(10) {}

	std::vector<Shape::Drawable> queue;
    Point root;
    double step_size;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {

        // Configuration for dots to appear when drawn
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        // Paints background in white
        cr->set_source_rgb(1, 1, 1);
        cr->paint();

        // Changes color to red
        cr->set_source_rgb(0.8, 0, 0);

        // Dummy line
        Point c1 {0, 0};
        Point c2 {110, 110};
        Shape::Drawable d(std::vector<Point> {c1, c2});
        queue.push_back(d);

        for (Shape::Drawable draw : queue) {
            draw_shape(cr, draw);
        }
        cr->stroke();

        return true;
    }

private:
	void draw_shape(
        const Cairo::RefPtr<Cairo::Context>& cr,
        const Shape::Drawable& draw) {

        int total_points = draw.points.size();

        // First point
        Point first_point = draw.points[0];
        double fx = first_point.x + root.x;
        double fy = first_point.y + root.y;
        cr->move_to(fx, fy);

        // Lines to other points
        for (int i = 1; i < total_points; i++) {
            Point point = draw.points[i];
            double px = point.x + root.x;
            double py = point.y + root.y;
            cr->line_to(px, py);
        }

        // Line from last point to first point
        cr->line_to(fx, fy);
    }

};

}  // namespace View

#endif  // CANVAS_H
