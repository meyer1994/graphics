#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <vector>

#include <cairomm/context.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>

#include "../mode/shape.h"
#include "../mode/point.h"
#include "../mode/window.h"

namespace Control {

class Viewport {
public:
    Viewport(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s, Window& w)
    : shapes(s),
      window(w) {

        shapes.push_back(Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 0),
            Point(50, 50),
            Point(0, 50)
        }));

        b->get_widget("drawing_area", drawing_area);
        b->get_widget("button_up", button_up);
        b->get_widget("button_down", button_down);
        b->get_widget("button_left", button_left);
        b->get_widget("button_right", button_right);
        b->get_widget("button_in", button_in);
        b->get_widget("button_out", button_out);

        connect_buttons();
        connect_draw();
    }

    ~Viewport() {}

    void move_up() {
        window.ymax += 10;
        window.ymin += 10;
        drawing_area->queue_draw();
    }

    void move_down() {
        window.ymax -= 10;
        window.ymin -= 10;
        drawing_area->queue_draw();
    }

    void move_left() {
        window.xmax -= 10;
        window.xmin -= 10;
        drawing_area->queue_draw();
    }

    void move_right() {
        window.xmax += 10;
        window.xmin += 10;
        drawing_area->queue_draw();
    }

    void zoom_in() {
        window.ymax -= 10;
        window.xmax -= 10;
        drawing_area->queue_draw();
    }

    void zoom_out() {
        window.ymax += 10;
        window.xmax += 10;
        drawing_area->queue_draw();
    }

    bool draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        // Configuration for dots to appear when drawn
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        // Paints background in white
        cr->set_source_rgb(1, 1, 1);
        cr->paint();

        // Changes color to red
        cr->set_source_rgb(0.8, 0, 0);

        // Draw all shapes
        for (int i = 0; i < shapes.size(); i++) {
            draw_shape(cr, shapes[i]);
        }
        cr->stroke();

        return true;
    }

    Gtk::DrawingArea* drawing_area = nullptr;
    std::vector<Shape>& shapes;
    Window& window;

    Gtk::Button* button_up = nullptr;
    Gtk::Button* button_down = nullptr;
    Gtk::Button* button_left = nullptr;
    Gtk::Button* button_right = nullptr;
    Gtk::Button* button_in = nullptr;
    Gtk::Button* button_out = nullptr;

protected:
    void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, Shape& shape) {
        int total_points = shape.points_real.size();

        // First point
        Point first_point = vp_transform(shape.points_real[0]);
        double fx = first_point[0];
        double fy = first_point[1];
        cr->move_to(fx, fy);

        // Lines to other points
        for (Point& point : shape.points_real) {
            Point n = vp_transform(point);
            cr->line_to(n[0], n[1]);
        }

        // Line from last point to first point
        cr->line_to(fx, fy);
    }

    Point vp_transform(Point& p) {
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double xvmax = alloc.get_width();
        double yvmax = alloc.get_height();

        double x = ((p[0] - window.xmin) / (window.xmax - window.xmin)) * (xvmax);
        double y = (1 - ((p[1] - window.ymin) / (window.ymax - window.ymin))) * (yvmax);
        return Point(x, y);
    }

    void connect_buttons() {
        button_up
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_up));

        button_down
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_down));

        button_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_left));

        button_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_right));

        button_in
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_in));

        button_out
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_out));
    }

    void connect_draw() {
        drawing_area
            ->signal_draw()
            .connect(sigc::mem_fun(*this, &Control::Viewport::draw));
    }
};

}  // namespace Control


#endif  // CONTROL_VIEWPORT_H