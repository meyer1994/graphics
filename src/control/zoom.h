#ifndef ZOOM_H
#define ZOOM_H

#include <vector>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include "../mode/drawable.h"

void zoom_in(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.scale(1.1);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

void zoom_out(std::vector<Drawable>* df, const Glib::RefPtr<Gtk::Builder>& builder) {
    for (Drawable& d : *df) {
        d.scale(0.9);
    }
    Gtk::DrawingArea* dr = nullptr;
    builder->get_widget("drawing_area", dr);
    dr->queue_draw();
}

#endif  // ZOOM_H