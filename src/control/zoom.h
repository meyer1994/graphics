#ifndef ZOOM_CONTROL_H
#define ZOOM_CONTROL_H

#include <gtkmm/drawingarea.h>
#include "../mode/window.h"

class ZoomControl {
public:
    ZoomControl(Window& win, Gtk::DrawingArea& draw)
    : window(win),
      drawing_area(draw) {}

    ~ZoomControl() {}
    
    void zoom_in() {
        window.ymax -= 10;
        window.xmax -= 10;
        drawing_area.queue_draw();
    }

    void zoom_out() {
        window.ymax += 10;
        window.xmax += 10;
        drawing_area.queue_draw();
    }

    Window& window;
    Gtk::DrawingArea& drawing_area;
};


#endif  // ZOOM_CONTROL_H