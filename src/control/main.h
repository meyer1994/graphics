#ifndef CONTROL_MAIN_H
#define CONTROL_MAIN_H

#include <vector>

#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>

#include "../mode/shape.h"
#include "../mode/window.h"
#include "viewport.h"
#include "dialog.h"

namespace Control {

class Main {
public:
    Main(Glib::RefPtr<Gtk::Builder>& b) {
        b->get_widget("window_main", window_main);
        window_main->set_default_size(1000, 600);
        window_main->show_all();

        Gtk::DrawingArea* d = nullptr;
        b->get_widget("drawing_area", d);
        auto alloc = d->get_allocation();

        window = new Window(alloc.get_width(), alloc.get_height(), 0, 0);
        shapes = new std::vector<Shape>();
        shape_labels = new std::vector<Gtk::Label*>();
        
        control_viewport = new Control::Viewport(b, *shapes, *window);
        control_dialog = new Control::Dialog(b, *shapes, *shape_labels);

    }

    ~Main() {
        delete window_main;
        delete window;
        delete control_viewport;
        delete control_dialog;
        delete shapes;

        for (int i = 0; i < shape_labels->size(); i++) {
            delete (*shape_labels)[i];
        }
        delete shape_labels;
    }

    Window* window;
    Control::Viewport* control_viewport;
    Control::Dialog* control_dialog;

    Gtk::Window* window_main = nullptr;

    std::vector<Shape>* shapes;
    std::vector<Gtk::Label*>* shape_labels;

};

} // namespace Control

#endif  // CONTROL_MAIN_H