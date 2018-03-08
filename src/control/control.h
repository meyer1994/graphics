#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>
#include <gtkmm/drawingarea.h>

#include "../mode/drawable.h"
#include "../mode/window.h"
#include "../mode/point.h"
#include "draw.h"
#include "movement.h"
#include "zoom.h"

class Control {
public:
    Control(Glib::RefPtr<Gtk::Builder>& builder)
    : builder(builder),
      shapes(),
      points_buffer() {

        // Show window
        Gtk::Window* window_main = nullptr;
        builder->get_widget("window_main", window_main);
        window_main->set_default_size(800, 500);
        window_main->show_all();

        // Add dummy shape (for tests)
        Drawable d(std::vector<Point> {
            Point(0, 0),
            Point(100, 0),
            Point(100, 100),
            Point(0, 100)
        });
        shapes.push_back(d);


        Gtk::DrawingArea* dr = nullptr;
        builder->get_widget("drawing_area", dr);
        Gtk::Allocation alloc = dr->get_allocation();
        window = new Window(alloc.get_width(), alloc.get_height(), 0, 0);
        
        draw_control = new DrawControl(*window, shapes);
        move_control = new MoveControl(*window, *dr);
        zoom_control = new ZoomControl(*window, *dr);

        connect_draw();
        connect_buttons();
    }

    ~Control() {
        for (Gtk::Label* l : shapes_labels) {
            delete l;
        }

        Gtk::Dialog* dialog_input = nullptr;
        builder->get_widget("dialog_input", dialog_input);
        delete dialog_input;

        Gtk::Window* window_main = nullptr;
        builder->get_widget("window_main", window_main);
        delete window_main;

        delete draw_control;
        delete window;
    }

    Window* window;
    DrawControl* draw_control;
    MoveControl* move_control;
    ZoomControl* zoom_control;
    Glib::RefPtr<Gtk::Builder>& builder;
    std::vector<Drawable> shapes;
    std::vector<Gtk::Label*> shapes_labels;
    std::vector<Point> points_buffer;

protected:
    void connect_draw() {
        Gtk::DrawingArea* dr = nullptr;
        builder->get_widget("drawing_area", dr);
        dr
            ->signal_draw()
            .connect(sigc::mem_fun(*draw_control, &DrawControl::draw));
    }

    void connect_buttons() {
        // Movement buttons
        Gtk::Button* button_up = nullptr;
        builder->get_widget("button_up", button_up);
        button_up
            ->signal_clicked()
            .connect(sigc::mem_fun(*move_control, &MoveControl::move_up));

        Gtk::Button* button_down = nullptr;
        builder->get_widget("button_down", button_down);
        button_down
            ->signal_clicked()
            .connect(sigc::mem_fun(*move_control, &MoveControl::move_down));

        Gtk::Button* button_left = nullptr;
        builder->get_widget("button_left", button_left);
        button_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*move_control, &MoveControl::move_left));

        Gtk::Button* button_right = nullptr;
        builder->get_widget("button_right", button_right);
        button_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*move_control, &MoveControl::move_right));

        // Zoom buttons
        Gtk::Button* button_in = nullptr;
        builder->get_widget("button_in", button_in);
        button_in
            ->signal_clicked()
            .connect(sigc::mem_fun(*zoom_control, &ZoomControl::zoom_in));

        Gtk::Button* button_out = nullptr;
        builder->get_widget("button_out", button_out);
        button_out
            ->signal_clicked()
            .connect(sigc::mem_fun(*zoom_control, &ZoomControl::zoom_out));

        // Show dialog button
        Gtk::Button* button_add_shape = nullptr;
        Gtk::Dialog* dialog_input = nullptr;
        builder->get_widget("button_add_shape", button_add_shape);
        builder->get_widget("dialog_input", dialog_input);
        button_add_shape
            ->signal_clicked()
            .connect(sigc::mem_fun(*dialog_input, &Gtk::Dialog::show));

        // Dialog buttons
        Gtk::Button* button_finish = nullptr;
        builder->get_widget("button_finish", button_finish);
        button_finish
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::add_shape));

        Gtk::Button* button_add_point = nullptr;
        builder->get_widget("button_add_point", button_add_point);
        button_add_point
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::add_point));

        Gtk::Button* button_cancel = nullptr;
        builder->get_widget("button_cancel", button_cancel);
        button_cancel
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::cancel));
    }

    void add_point() {
        Gtk::Entry* text_input_x = nullptr;
        Gtk::Entry* text_input_y = nullptr;
        builder->get_widget("text_input_x", text_input_x);
        builder->get_widget("text_input_y", text_input_y);

        try {
            std::string sx = text_input_x->get_text();
            std::string sy = text_input_y->get_text();
            double x = std::stod(sx);
            double y = std::stod(sy);
            update_text_points_added(sx, sy);
            points_buffer.push_back(Point(x, y));
        } catch(std::exception& e) {
            // Nothing
        }

        // Clear inputs
        text_input_x->set_text("");
        text_input_y->set_text("");
    }

    void update_text_points_added(std::string x, std::string y) {
        Gtk::TextView* text_points_added;
        builder->get_widget("text_points_added", text_points_added);
        std::string current = text_points_added->get_buffer()->get_text();
        current += "(" + x + ", " + y + ")\n";
        text_points_added->get_buffer()->set_text(current);
    }

    void add_shape() {
        Gtk::Box* list_shapes = nullptr;
        Gtk::Entry* text_input_name = nullptr;
        Gtk::TextView* text_points_added = nullptr;
        Gtk::DrawingArea* drawing_area = nullptr;
        builder->get_widget("list_shapes", list_shapes);
        builder->get_widget("text_input_name", text_input_name);
        builder->get_widget("text_points_added", text_points_added);
        builder->get_widget("drawing_area", drawing_area);

        // Create shape
        shapes.push_back(Drawable(points_buffer));

        // Clear points
        points_buffer.clear();
        text_points_added->get_buffer()->set_text("");

        // Add shape to list
        std::string name = text_input_name->get_text();
        Gtk::Label* l = new Gtk::Label(name);
        shapes_labels.push_back(l);
        list_shapes->add(*l);
        l->show();

        // Close dialog
        Gtk::Dialog* dialog_input = nullptr;
        builder->get_widget("dialog_input", dialog_input);
        dialog_input->hide();

        // Update drawing area
        drawing_area->queue_draw();
    }

    void cancel() {
        // Close dialog
        Gtk::Dialog* dialog_input = nullptr;
        builder->get_widget("dialog_input", dialog_input);
        dialog_input->hide();
    }

};

#endif  // CONTROL_H