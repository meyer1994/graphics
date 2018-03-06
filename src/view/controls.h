#ifndef CONTROLS_H
#define CONTROLS_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>

class Controls : public Gtk::Grid {
public:
	Controls()
     : button_up("Up"),
       button_down("Down"),
       button_left("Left"),
       button_right("Right"),
       button_in("In"),
       button_out("Out") {

        set_border_width(5);
        set_row_spacing(5);
        set_column_spacing(5);

        attach(button_up, 1, 0, 1, 1);
        attach(button_down, 1, 2, 1, 1);
        attach(button_left, 0, 1, 1, 1);
        attach(button_right, 2, 1, 1, 1);

        attach(button_in, 4, 0, 1, 1);
        attach(button_out, 4, 2, 1, 1);
    }

    Gtk::Button button_up;
    Gtk::Button button_down;
    Gtk::Button button_left;
    Gtk::Button button_right;

    Gtk::Button button_in;
    Gtk::Button button_out;

};

#endif  // CONTROLS_H