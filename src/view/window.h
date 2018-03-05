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

        controls
            .button_up
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &Window::move_up));
        controls
            .button_down
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &Window::move_down));
        controls
            .button_left
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &Window::move_left));
        controls
            .button_right
            .signal_clicked()
            .connect(sigc::mem_fun(*this, &Window::move_right));
    }

    View::Canvas canvas;
    View::Controls controls;
    Gtk::Box box;

private:
    void move_up() {
        canvas.root.y -= canvas.step_size;
        canvas.queue_draw();
    }

    void move_down() {
        canvas.root.y += canvas.step_size;
        canvas.queue_draw();
    }

    void move_left() {
        canvas.root.x -= canvas.step_size;
        canvas.queue_draw();
    }

    void move_right() {
        canvas.root.x += canvas.step_size;
        canvas.queue_draw();
    }

};

}  // namespace View

#endif  // WINDOW_H