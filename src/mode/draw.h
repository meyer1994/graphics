#ifndef DRAW_H
#define DRAW_H

#include "point.h"
#include "drawable.h"
#include "display_file.h"

void draw_shape(
    const Cairo::RefPtr<Cairo::Context>& cr,
    Drawable& draw,
    DisplayFile* df) {

    int total_points = draw.points.size();

    // First point
    Point first_point = draw.points[0];
    double fx = first_point.x + df->root_point.x;
    double fy = first_point.y + df->root_point.y;
    cr->move_to(fx, fy);

    // Lines to other points
    for (int i = 1; i < total_points; i++) {
        Point point = draw.points[i];
        double px = point.x + df->root_point.x;
        double py = point.y + df->root_point.y;
        cr->line_to(px, py);
    }

    // Line from last point to first point
    cr->line_to(fx, fy);
}

bool draw(const Cairo::RefPtr<Cairo::Context>& cr, DisplayFile* df) {
    // Configuration for dots to appear when drawn
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // Paints background in white
    cr->set_source_rgb(1, 1, 1);
    cr->paint();

    // Changes color to red
    cr->set_source_rgb(0.8, 0, 0);

    // Draw all shapes
    for (Drawable draw : df->shapes_list) {
        draw_shape(cr, draw, df);
    }
    cr->stroke();

    return true;
}

#endif  // DRAW_H