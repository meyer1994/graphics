#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <gtkmm/drawingarea.h>
#include "display_file.h"

void move_up(
	Cairo::RefPtr<Cairo::Context>& cr,
	DisplayFile& df,
	Gtk::DrawingArea* dr) {

	df.root_point.y -= df.step_size;
	dr->queue_draw();
}

void move_down(
	Cairo::RefPtr<Cairo::Context>& cr,
	DisplayFile& df,
	Gtk::DrawingArea* dr) {

	df.root_point.y += df.step_size;
	dr->queue_draw();
}

void move_left(
	Cairo::RefPtr<Cairo::Context>& cr,
	DisplayFile& df,
	Gtk::DrawingArea* dr) {

	df.root_point.x -= df.step_size;
	dr->queue_draw();
}

void move_right(
	Cairo::RefPtr<Cairo::Context>& cr,
	DisplayFile& df,
	Gtk::DrawingArea* dr) {

	df.root_point.x += df.step_size;
	dr->queue_draw();
}

#endif  // MOVEMENT_H