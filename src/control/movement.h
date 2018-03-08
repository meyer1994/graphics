#ifndef MOVE_CONTROL_H
#define MOVE_CONTROL_H

#include <gtkmm/drawingarea.h>
#include "../mode/window.h"

class MoveControl {
public:
    MoveControl(Window& win, Gtk::DrawingArea& draw) 
    : window(win),
      drawing_area(draw) {}

    ~MoveControl() {}

    void move_up() {
        window.ymax += 10;
        window.ymin += 10;
        drawing_area.queue_draw();
    }

    void move_down() {
        window.ymax -= 10;
        window.ymin -= 10;
        drawing_area.queue_draw();
    }

    void move_left() {
        window.xmax -= 10;
        window.xmin -= 10;
        drawing_area.queue_draw();
    }

    void move_right() {
        window.xmax += 10;
        window.xmin += 10;
        drawing_area.queue_draw();
    }

    Window& window;
    Gtk::DrawingArea& drawing_area;
};


#endif  // MOVE_CONTROL_H