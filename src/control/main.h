#ifndef CONTROL_MAIN_H
#define CONTROL_MAIN_H

#include <vector>

#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>

#include "../mode/shape.h"
#include "../mode/window.h"
#include "file_dialog.h"
#include "viewport.h"
#include "dialog.h"
#include "shapes.h"

namespace Control {

class Main {
public:
    Main(Glib::RefPtr<Gtk::Builder>& b) {
        b->get_widget("window_main", window_main);
        window_main->set_default_size(1000, 600);
        window_main->show_all();

        shapes = new std::vector<Shape>();
        shape_labels = new std::vector<Gtk::Label*>();

        window = new Window(b, *shapes);

        control_viewport = new Viewport(b, *shapes, *window);
        control_dialog = new Dialog(b, *shapes);
        control_shapes = new Shapes(b, *shapes);
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

    std::vector<Shape>* shapes = nullptr;
    std::vector<Gtk::Label*>* shape_labels = nullptr;

    Window* window = nullptr;

    Viewport* control_viewport = nullptr;
    Dialog* control_dialog = nullptr;
    Shapes* control_shapes = nullptr;

    Gtk::Window* window_main = nullptr;

};

} // namespace Control

#endif  // CONTROL_MAIN_H
