#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include <gtkmm/drawingarea.h>
#include "drawable.h"
#include "display_file.h"

void move_up(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable d : df->shapes_list) {
        d.scale(1.5);
        // Point p = d.get_medium_point();
    }
	dr->queue_draw();
}

void move_down(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable& d : df->shapes_list) {
        d.translate(0, 10);
    }
    dr->queue_draw();
}

void move_left(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable& d : df->shapes_list) {
        d.translate(-10, 0);
    }
	dr->queue_draw();
}

void move_right(DisplayFile* df, Gtk::DrawingArea* dr) {
    for (Drawable& d : df->shapes_list) {
        d.translate(10, 0);
    }
	dr->queue_draw();
}

#endif  // MOVEMENT_H