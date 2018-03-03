#include "controls.h"

View::Controls::Controls() 
{
	add(directional);
	add(zoom);

	show_all();
}

View::Controls::~Controls() {}