#ifndef ZOOM_CONTROL_H
#define ZOOM_CONTROL_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>

class Zoom : public Gtk::VBox {
public:
	Zoom();
	~Zoom();
	
	Gtk::Button in;
	Gtk::Button out;
};

#endif  // ZOOM_CONTROL_H