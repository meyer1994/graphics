#ifndef CONTROL_MAIN_H
#define CONTROL_MAIN_H

#include <vector>

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/shapes/polygon.h"
#include "../mode/shapes/shape.h"
#include "../mode/shapes/bezier_curve.h"
#include "../mode/shapes/spline.h"
#include "../mode/window.h"
#include "../mode/viewport.h"

#include "dialog.h"
#include "shapes.h"
#include "viewport.h"
// #include "filechooser.h"

namespace Control {

class Main {
public:
    Main(Glib::RefPtr<Gtk::Builder>& b) {
        // Creates main window
        b->get_widget("window_main", window_main);
        window_main->set_default_size(1000, 600);
        window_main->show_all();

        // Dummy polygon (debugging)
        Polygon* s = new Polygon(std::vector<Point>{
			Point(0, 100),
			Point(100, 100),
			Point(100, 0),
			Point(50, 50),
			Point(0, 0)
        });
        s->filled = true;
        shapes.push_back(s);

        // Dummy curve (debugging)
        Spline* bc = new Spline{
            Point(0, 0),
            Point(0, 0),
            Point(0, 0),
            Point(0, 0),
            Point(100, 100),
            Point(200, 0),
            Point(300, 100),
            Point(400, 300),
            Point(500, 0),
            Point(600, 100)
        };
        shapes.push_back(bc);


        // Add text to combo box
        Gtk::ComboBoxText* c = nullptr;
        b->get_widget("combobox_shapes", c);
        c->append("poligono");
        c->append("curva");

        // Gets size to pass to window
        Gtk::DrawingArea* drawing_area = nullptr;
        b->get_widget("drawing_area", drawing_area);
        const Gtk::Allocation alloc = drawing_area->get_allocation();
        const double width = alloc.get_width();
        const double height = alloc.get_height();

        // Modes
        window = Mode::Window(width, height);
        mode_viewport = new Mode::Viewport(window, shapes, *drawing_area);

        // Controllers
        control_viewport = new Control::Viewport(b, *mode_viewport);
        control_dialog = new Control::Dialog(b, *mode_viewport);
        control_shapes = new Control::Shapes(b, *mode_viewport);
        // control_filechooser = new Control::FileChooser(b, *mode_viewport);
    }

    virtual ~Main() {
        // View
        delete window_main;

        // Control
        delete control_viewport;
        delete control_dialog;
        // delete control_filechooser;

        // Mode
        delete mode_viewport;

        // Clear shapes
        for (Shape* s : shapes) {
            delete s;
        }
    }

    // View
    Gtk::Window* window_main = nullptr;

protected:
    // Mode
    Mode::Viewport* mode_viewport = nullptr;
    std::vector<Shape*> shapes;
    Mode::Window window;

    // Controllers
    Control::Viewport* control_viewport = nullptr;
    Control::Dialog* control_dialog = nullptr;
    Control::Shapes* control_shapes = nullptr;
    // Control::FileChooser* control_filechooser = nullptr;
};

} // namespace Control

#endif  // CONTROL_MAIN_H
