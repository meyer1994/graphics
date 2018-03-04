#include "window.h"

View::Window::Window() {
    set_border_width(10);

    box.set_spacing(10);
    box.set_homogeneous();
    box.add(controls);
    box.add(canvas);
    
    add(box);

    show_all();
}

View::Window::~Window() {}