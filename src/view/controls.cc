#include "controls.h"

View::Controls::Controls() {
    attach(directional, 0, 0, 1, 1);
    attach(zoom, 1, 0, 1, 1);

    set_border_width(5);
    set_row_spacing(5);
    set_column_spacing(5);
}

View::Controls::~Controls() {}