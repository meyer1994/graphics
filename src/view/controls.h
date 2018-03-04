#ifndef CONTROLS_H
#define CONTROLS_H

#include <gtkmm/grid.h>
#include "controls/directional.h"
#include "controls/zoom.h"

namespace View {

class Controls : public Gtk::Grid {
public:
	Controls() {
        attach(directional, 0, 0, 1, 1);
        attach(zoom, 1, 0, 1, 1);

        set_border_width(5);
        set_row_spacing(5);
        set_column_spacing(5);
    }

	~Controls() {}

	Directional directional;
	Zoom zoom;
};

}  // namesapce View

#endif  // CONTROLS_H