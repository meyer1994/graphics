#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "canvas.h"
#include "controls.h"

namespace View {

class Window : public Gtk::Window {
public:
    Window() {
        box.set_spacing(10);
        box.pack_start(controls, false, false, 0);
        box.pack_start(canvas, true, true, 0);
        
        set_border_width(10);
        add(box);
        show_all();
    }

    View::Canvas canvas;
    View::Controls controls;
    Gtk::Box box;
};

}  // namespace View

#endif  // WINDOW_H