#include "controls_view.h"

Components::ControlsView::ControlsView() :
zoom(),
directional()
{
	add(directional);
	add(zoom);

	show_all();
}

Components::ControlsView::~ControlsView() {}