#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include "../mode/drawable.h"

void move_up(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.translate(0, -10);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

void move_down(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.translate(0, 10);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

void move_left(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.translate(-10, 0);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

void move_right(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.translate(10, 0);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

#endif  // MOVEMENT_H