#ifndef CONTROLS_H
#define CONTROLS_H

#include <gtkmm/grid.h>
#include "controls/directional.h"
#include "controls/zoom.h"

namespace View {

class Controls : public Gtk::Grid {
public:
	Controls();
	~Controls();

	Directional directional;
	Zoom zoom;
};

}  // namesapce View

#endif  // CONTROLS_H