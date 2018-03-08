#ifndef DRAW_H
#define DRAW_H

#include <cairo.h>
#include "../mode/point.h"
#include "../mode/drawable.h"

void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, Drawable& draw) {

    int total_points = draw.points.size();

    // First point
    Point first_point = draw.points[0];
    double fx = first_point.x;
    double fy = first_point.y;
    cr->move_to(fx, fy);

    // Lines to other points
    for (Point& point : draw.points) {
        double px = point.x;
        double py = point.y;
        cr->line_to(px, py);
    }

    // Line from last point to first point
    cr->line_to(fx, fy);
}

bool draw(const Cairo::RefPtr<Cairo::Context>& cr, std::vector<Drawable>* df) {
    // Configuration for dots to appear when drawn
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);
    // Paints background in white
    cr->set_source_rgb(1, 1, 1);
    cr->paint();

    // Changes color to red
    cr->set_source_rgb(0.8, 0, 0);

    // Draw all shapes
    for (Drawable& draw : *df) {
        draw_shape(cr, draw);
    }
    cr->stroke();

    return true;
}

#endif  // DRAW_H