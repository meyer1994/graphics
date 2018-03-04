#ifndef ZOOM_CONTROL_H
#define ZOOM_CONTROL_H

#include <gtkmm/grid.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class Zoom : public Gtk::Frame {
public:
	Zoom();
	~Zoom();
	
	Gtk::Button in;
	Gtk::Button out;
    Gtk::Grid grid;
};

#endif  // ZOOM_CONTROL_H