#ifndef CONTROL_MAIN_H
#define CONTROL_MAIN_H

#include <vector>

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/shape.h"
#include "../mode/window.h"
#include "../mode/viewport.h"

#include "dialog.h"
#include "shapes.h"
#include "viewport.h"
#include "filechooser.h"

namespace Control {

class Main {
public:
    Main(Glib::RefPtr<Gtk::Builder>& b) {

        // Creates main window
        b->get_widget("window_main", window_main);
        window_main->set_default_size(1000, 600);
        window_main->show_all();

        // Dummy shape (debugging)
        shapes.push_back(Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 0),
            Point(50, 50)
        }));
        Gtk::ComboBoxText* c = nullptr;
        b->get_widget("combobox_shapes", c);
        c->append("teste");

        Gtk::DrawingArea* drawing_area = nullptr;
        b->get_widget("drawing_area", drawing_area);
        Gtk::Allocation alloc = drawing_area->get_allocation();
        double width = alloc.get_width();
        double height = alloc.get_height();

        // Modes
        window = Window(width, height);
        mode_viewport = new Mode::Viewport(window, shapes, *drawing_area);

        // Controllers
        control_viewport = new Viewport(b, *mode_viewport);
        control_dialog = new Dialog(b, *mode_viewport);
        control_shapes = new Shapes(b, *mode_viewport);
        control_filechooser = new FileChooser(b, *mode_viewport);
    }

    ~Main() {
        // View
        delete window_main;

        // Control
        delete control_viewport;
        delete control_dialog;
        delete control_filechooser;

        // Mode
        delete mode_viewport;
    }

    // View
    Gtk::Window* window_main = nullptr;

    // Mode
    Mode::Viewport* mode_viewport = nullptr;
    std::vector<Shape> shapes;
    Window window;

    // Controllers
    Viewport* control_viewport = nullptr;
    Dialog* control_dialog = nullptr;
    Shapes* control_shapes = nullptr;
    FileChooser* control_filechooser = nullptr;
};

} // namespace Control

#endif  // CONTROL_MAIN_H
