#ifndef CONTROL_MAIN_H
#define CONTROL_MAIN_H

#include <vector>

#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/shape.h"
#include "../mode/window.h"
#include "../mode/viewport.h"

#include "filechooser.h"
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

        // Dummy shape (debugging)
        shapes->push_back(Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 0),
            Point(50, 50)
        }));
        shapes->push_back(Line(Point(0, 0), Point(50, 50)));
        Gtk::ComboBoxText* c = nullptr;
        b->get_widget("combobox_shapes", c);
        c->append("teste");

        shape_labels = new std::vector<Gtk::Label*>();

        Gtk::DrawingArea* drawing_area = nullptr;
        b->get_widget("drawing_area", drawing_area);
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double width = alloc.get_width();
        double height = alloc.get_height();

        window = new Window(width, height);
        mode_viewport = new Mode::Viewport(*window, *shapes, *drawing_area);

        control_viewport = new Viewport(b, *mode_viewport);
        control_dialog = new Dialog(b, *shapes);
        control_shapes = new Shapes(b, *shapes);
        file_chooser = new FileChooser(b, *shapes);
    }

    ~Main() {
        delete window_main;
        delete window;
        delete control_viewport;
        delete control_dialog;
        delete shapes;
        delete file_chooser;

        for (int i = 0; i < shape_labels->size(); i++) {
            delete (*shape_labels)[i];
        }
        delete shape_labels;
    }

    std::vector<Shape>* shapes = nullptr;
    std::vector<Gtk::Label*>* shape_labels = nullptr;

    Window* window = nullptr;

    Mode::Viewport* mode_viewport = nullptr;

    // Controllers
    Viewport* control_viewport = nullptr;
    Dialog* control_dialog = nullptr;
    Shapes* control_shapes = nullptr;
    FileChooser* file_chooser = nullptr;

    Gtk::Window* window_main = nullptr;

};

} // namespace Control

#endif  // CONTROL_MAIN_H
