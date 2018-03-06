#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include "controls.h"

class Window : public Gtk::Window {
public:
    Window() {
        // Box properties
        box.set_spacing(10);
        box.pack_start(controls, false, false, 0);
        box.pack_start(canvas, true, true, 0);

        // Window properties
        set_position(Gtk::WIN_POS_CENTER);
        set_title("Computer Graphics, by J. Meyer & G. Bueno");
        set_default_size(500, 500);
        set_border_width(10);
        add(box);
        show_all();
    }

    Controls controls;
    Gtk::DrawingArea canvas;
    Gtk::Box box;
};

#endif  // WINDOW_H
