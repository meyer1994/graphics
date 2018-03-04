#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "canvas.h"
#include "controls.h"

namespace View {

class Window : public Gtk::Window {
public:
    Window();
    ~Window();

protected:
    View::Canvas canvas;
    View::Controls controls;
    Gtk::Box box;
};

}  // namespace View

#endif  // WINDOW_H