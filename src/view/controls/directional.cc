#include "directional.h"

Directional::Directional() :
button_up("Up"),
button_down("Down"),
button_left("Left"),
button_right("Right")
{
	attach(button_up, 1, 0, 1, 1);
	attach(button_down, 1, 2, 1, 1);
	attach(button_left, 0, 1, 1, 1);
	attach(button_right, 2, 1, 1, 1);
}

Directional::~Directional() {}