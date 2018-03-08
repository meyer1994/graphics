#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "../mode/point.h"
#include "../mode/window.h"
#include "../mode/drawable.h"

class DrawControl {
public:
    DrawControl(Window& win, std::vector<Drawable>& df) {
        draw_area = dr;
        window = win;
        display_file = df;
    }
    ~DrawControl() {}

    bool draw(const Cairo::RefPtr<Cairo::Context>& cr) {
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
    
    double xvmax = window.xmax;
    double yvmax = window.ymax;
    Window& window;
    std::vector<Drawable>& display_file;


protected:
    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr) {

        int total_points = draw.points.size();

        // First point
        Point first_point = draw.points[0];
        double fx = first_point.x;
        double fy = first_point.y;
        cr->move_to(fx, fy);

        // Lines to other points
        for (Point& point : draw.points) {
            Point n = vp_transform(point);
            cr->line_to(n.x, n.y);
        }

        // Line from last point to first point
        cr->line_to(fx, fy);
    }

    Point vp_transform(Point& p) {
        double x = ((p.x - window.xmax) / (window.xmax - window.xmin)) * (xvmax);
        double y = (1 - ((p.y - window.ymax) / (window.ymax - window.ymin))) * (yvmax);
    }

};


#endif  // DRAW_H