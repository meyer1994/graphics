#ifndef ZOOM_CONTROL_H
#define ZOOM_CONTROL_H

#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class Zoom : public Gtk::Frame {
public:
	Zoom() : Gtk::Frame("Zoom"),
        in("In"),
        out("Out")
    {
        grid.attach(in, 0, 0, 1, 1);
        grid.attach(out, 0, 1, 1, 1);
        grid.set_border_width(5);
        grid.set_row_spacing(5);
        grid.set_column_spacing(5);

        add(grid);
    }

	~Zoom() {}
	
	Gtk::Button in;
	Gtk::Button out;
    Gtk::Grid grid;
};

#endif  // ZOOM_CONTROL_H