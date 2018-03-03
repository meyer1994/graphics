#ifndef CONTROLS_H
#define CONTROLS_H

#include <gtkmm/box.h>
#include "controls/directional.h"
#include "controls/zoom.h"

namespace View {

class Controls : public Gtk::VBox {
public:
	Controls();
	~Controls();

	Directional directional;
	Zoom zoom;
};

}  // namesapce View

#endif  // CONTROLS_H