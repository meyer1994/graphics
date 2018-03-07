#ifndef CONTROL_H
#define CONTROL_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/button.h>

#include "view/view.h"
#include "mode/display_file.h"
#include "mode/draw.h"
#include "mode/zoom.h"
#include "mode/movement.h"

class Control {
public:
    Control(View& view, DisplayFile& display_file)
    : view(view),
      display_file(display_file) {
        connect_draw();
        connect_buttons();
    }
    
    ~Control() {}

    void connect_draw() {
        Gtk::DrawingArea* drawing_area = nullptr;
        view.builder->get_widget("drawing_area", drawing_area);

        auto binded = sigc::bind(&draw, &display_file);
        drawing_area->signal_draw().connect(binded);
    }

    void connect_buttons() {
        Gtk::DrawingArea* drawing_area = nullptr;
        view.builder->get_widget("drawing_area", drawing_area);

        Gtk::Button* button_up = nullptr;
        view.builder->get_widget("button_up", button_up);
        auto bind_up = sigc::bind(&move_up, &display_file, drawing_area);
        button_up->signal_clicked().connect(bind_up);

        Gtk::Button* button_down = nullptr;
        view.builder->get_widget("button_down", button_down);
        auto bind_down = sigc::bind(&move_down, &display_file, drawing_area);
        button_down->signal_clicked().connect(bind_down);

        Gtk::Button* button_left = nullptr;
        view.builder->get_widget("button_left", button_left);
        auto bind_left = sigc::bind(&move_left, &display_file, drawing_area);
        button_left->signal_clicked().connect(bind_left);

        Gtk::Button* button_right = nullptr;
        view.builder->get_widget("button_right", button_right);
        auto bind_right = sigc::bind(&move_right, &display_file, drawing_area);
        button_right->signal_clicked().connect(bind_right);

        Gtk::Button* button_in = nullptr;
        view.builder->get_widget("button_in", button_in);
        auto bind_in = sigc::bind(&zoom_in, &display_file, drawing_area);
        button_in->signal_clicked().connect(bind_in);

        Gtk::Button* button_out = nullptr;
        view.builder->get_widget("button_out", button_out);
        auto bind_out = sigc::bind(&zoom_out, &display_file, drawing_area);
        button_out->signal_clicked().connect(bind_out);
    }

    View view;
    DisplayFile display_file;       
};

#endif  // CONTROL_H