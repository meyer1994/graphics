#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <gtkmm/drawingarea.h>
#include "display_file.h"

void move_up(DisplayFile* df, Gtk::DrawingArea* dr) {
	df->root_point.y -= df->step_size;
	dr->queue_draw();
}

void move_down(DisplayFile* df, Gtk::DrawingArea* dr) {
	df->root_point.y += df->step_size;
	dr->queue_draw();
}

void move_left(DisplayFile* df, Gtk::DrawingArea* dr) {
	df->root_point.x -= df->step_size;
	dr->queue_draw();
}

void move_right(DisplayFile* df, Gtk::DrawingArea* dr) {
	df->root_point.x += df->step_size;
	dr->queue_draw();
}

#endif  // MOVEMENT_H