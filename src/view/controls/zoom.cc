#include "zoom.h"

Zoom::Zoom() : Gtk::Frame("Zoom"),
in("In"),
out("Out")
{
    grid.attach(in, 0, 0, 1, 1);
	grid.attach(out, 1, 0, 1, 1);
    grid.set_border_width(5);
    grid.set_row_spacing(5);
    grid.set_column_spacing(5);

    add(grid);
}

Zoom::~Zoom() {}

