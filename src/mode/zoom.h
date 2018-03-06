#ifndef ZOOM_H
#define ZOOM_H

#include <gtkmm/drawingarea.h>
#include "display_file.h"
#include "drawable.h"

void zoom_in(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable& d : df->shapes_list) {
        d.scale(1.1);
    }
    dr->queue_draw();
}

void zoom_out(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable& d : df->shapes_list) {
        d.scale(0.9);
    }
    dr->queue_draw();
}

#endif  // ZOOM_H