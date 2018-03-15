#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>

class Window {
public:
	Window(Glib::RefPtr<Gtk::Builder>& b) {
        Gtk::DrawingArea* d = nullptr;
        b->get_widget("drawing_area", d);
        Gtk::Allocation alloc = d->get_allocation();

        xmax = alloc.get_width();
        ymax = alloc.get_width();
        xmin = 0;
        ymin = 0;
	}

	~Window() {}
	
	double xmax;
	double ymax;
	double xmin;
	double ymin;
};

#endif  // WINDOW_H