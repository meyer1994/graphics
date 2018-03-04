#ifndef DIRECTIONAL_CONTROL_H
#define DIRECTIONAL_CONTROL_H

#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class Directional : public Gtk::Frame {
public:
	Directional() : Gtk::Frame("Move"),
        button_up("Up"),
        button_down("Down"),
        button_left("Left"),
        button_right("Right")
    {
        grid.attach(button_up, 1, 0, 1, 1);
        grid.attach(button_down, 1, 2, 1, 1);
        grid.attach(button_left, 0, 1, 1, 1);
        grid.attach(button_right, 2, 1, 1, 1);
        grid.set_border_width(5);
        grid.set_row_spacing(5);
        grid.set_column_spacing(5);

        add(grid);
    }

	~Directional() {}

	Gtk::Button button_up;
	Gtk::Button button_down;
	Gtk::Button button_left;
	Gtk::Button button_right;
    Gtk::Grid grid;
};

#endif  // DIRECTIONAL_CONTROL_H