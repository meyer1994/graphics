#include "zoom.h"

Components::Controls::Zoom::Zoom() :
in("In"),
out("Out")
{
	add(in);
	add(out);
}

Components::Controls::Zoom::~Zoom() {}

