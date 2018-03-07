#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include "../mode/drawable.h"
#include "../view/view.h"

void move_up(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.translate(0, -10);
    }
    view->window.drawing_area->queue_draw();
}

void move_down(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.translate(0, 10);
    }
    view->window.drawing_area->queue_draw();
}

void move_left(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.translate(-10, 0);
    }
	view->window.drawing_area->queue_draw();
}

void move_right(std::vector<Drawable>* df, View* view) {
    for (Drawable& d : *df) {
        d.translate(10, 0);
    }
	view->window.drawing_area->queue_draw();
}

#endif  // MOVEMENT_H