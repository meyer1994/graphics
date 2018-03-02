#ifndef CONTROLS_VIEW_H
#define CONTROLS_VIEW_H

#include <gtkmm/box.h>
#include "controls/directional.h"
#include "controls/zoom.h"

namespace Components {

class ControlsView : public Gtk::VBox {
public:
	ControlsView();
	~ControlsView();

	Components::Controls::Directional directional;
	Components::Controls::Zoom zoom;
};

}  // namespace Components

#endif  // CONTROLS_VIEW_H