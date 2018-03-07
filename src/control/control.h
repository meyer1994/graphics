#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include "../mode/drawable.h"
#include "draw.h"
#include "movement.h"
#include "zoom.h"

class Control {
public:
    Control(Glib::RefPtr<Gtk::Builder>& builder) : builder(builder) {
        Drawable d(std::vector<Point> {
            Point(0, 0),
            Point(100, 0),
            Point(100, 100),
            Point(0, 100)
        });
        shapes.push_back(d);

        connect_draw();
        connect_buttons();
    }
    ~Control() {}

    Glib::RefPtr<Gtk::Builder>& builder;
    std::vector<Drawable> shapes;

protected:
    void connect_draw() {
        auto binded = sigc::bind(&draw, &shapes);
        Gtk::DrawingArea* dr = nullptr;
        builder->get_widget("drawing_area", dr);
        dr->signal_draw().connect(binded);
    }

    void connect_buttons() {
        auto bind_up = sigc::bind(&move_up, &shapes, builder);
        Gtk::Button* button_up = nullptr;
        builder->get_widget("button_up", button_up);
        button_up->signal_clicked().connect(bind_up);

        auto bind_down = sigc::bind(&move_down, &shapes, builder);
        Gtk::Button* button_down = nullptr;
        builder->get_widget("button_down", button_down);
        button_down->signal_clicked().connect(bind_down);

        auto bind_left = sigc::bind(&move_left, &shapes, builder);
        Gtk::Button* button_left = nullptr;
        builder->get_widget("button_left", button_left);
        button_left->signal_clicked().connect(bind_left);

        auto bind_right = sigc::bind(&move_right, &shapes, builder);
        Gtk::Button* button_right = nullptr;
        builder->get_widget("button_right", button_right);
        button_right->signal_clicked().connect(bind_right);

        auto bind_in = sigc::bind(&zoom_in, &shapes, builder);
        Gtk::Button* button_in = nullptr;
        builder->get_widget("button_in", button_in);
        button_in->signal_clicked().connect(bind_in);

        auto bind_out = sigc::bind(&zoom_out, &shapes, builder);
        Gtk::Button* button_out = nullptr;
        builder->get_widget("button_out", button_out);
        button_out->signal_clicked().connect(bind_out);
    }
    
};

#endif  // CONTROL_H