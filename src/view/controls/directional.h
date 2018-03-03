#ifndef DIRECTIONAL_CONTROL_H
#define DIRECTIONAL_CONTROL_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>

class Directional : public Gtk::Grid {
public:
	Directional();
	~Directional();

	Gtk::Button button_up;
	Gtk::Button button_down;
	Gtk::Button button_left;
	Gtk::Button button_right;
};

#endif  // DIRECTIONAL_CONTROL_H