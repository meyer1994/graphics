#ifndef ZOOM_H
#define ZOOM_H

#include <vector>
#include "../view/view.h"
#include "../mode/drawable.h"

void zoom_in(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.scale(1.1);
    }
    view->window.drawing_area->queue_draw();
}

void zoom_out(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.scale(0.9);
    }
    view->window.drawing_area->queue_draw();
}

#endif  // ZOOM_H