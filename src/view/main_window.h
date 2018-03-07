#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>

class MainWindow {
public:
    MainWindow() {
        builder = Gtk::Builder::create_from_file("src/view/main_window.glade");

        builder->get_widget("window_main", window_main);
        builder->get_widget("button_up", button_up);
        builder->get_widget("button_down", button_down);
        builder->get_widget("button_left", button_left);
        builder->get_widget("button_right", button_right);
        builder->get_widget("button_in", button_in);
        builder->get_widget("button_out", button_out);
        builder->get_widget("drawing_area", drawing_area);
    }

    ~MainWindow() {}

    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Window* window_main;
    Gtk::Button* button_up;
    Gtk::Button* button_down;
    Gtk::Button* button_left;
    Gtk::Button* button_right;
    Gtk::Button* button_in;
    Gtk::Button* button_out;
    Gtk::DrawingArea* drawing_area;
};

#endif  // MAIN_WINDOW_H