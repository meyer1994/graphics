#ifndef CONTROL_SHAPES_H
#define CONTROL_SHAPES_H

#include <string>
#include <vector>

#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/comboboxtext.h>

namespace Control {

class Shapes {
public:
    Shapes(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s)
    : shapes(s) {

        // Get combo box
        b->get_widget("combobox_shapes", combobox_shapes);

        // Get drawing area
        b->get_widget("drawing_area", drawing_area);

        // Get movement widgets
        b->get_widget("button_shape_move_up", button_move_up);
        b->get_widget("button_shape_move_down", button_move_down);
        b->get_widget("button_shape_move_left", button_move_left);
        b->get_widget("button_shape_move_right", button_move_right);
        b->get_widget("input_shape_move", input_move);

        // Get inflate widgets
        b->get_widget("button_shape_inflate_plus", button_inflate_plus);
        b->get_widget("button_shape_inflate_minus", button_inflate_minus);
        b->get_widget("input_shape_inflate", input_inflate);

        // Get rotation widgets
        // radio buttons
        b->get_widget("radiobutton_shape_object_rotate", radio_shape);
        b->get_widget("radiobutton_shape_viewport_rotate", radio_viewport);
        b->get_widget("radiobutton_shape_point_rotate", radio_coord);
        // entries
        b->get_widget("input_shape_rotation_x", input_rotate_x);
        b->get_widget("input_shape_rotation_y", input_rotate_y);
        b->get_widget("input_shape_rotation_z", input_rotate_z);
        b->get_widget("input_shape_rotation_angle", input_angle);
        // buttons
        b->get_widget("button_shape_rotate_left", button_rotate_left);
        b->get_widget("button_shape_rotate_right", button_rotate_right);
    }

    ~Shapes() {

    }

    // Shapes to be drawn
    std::vector<Shape>& shapes;

    // Drawing area
    Gtk::DrawingArea* drawing_area = nullptr;

    // Combobox
    Gtk::ComboBoxText* combobox_shapes = nullptr;

    // Movement
    Gtk::Button* button_move_up = nullptr;
    Gtk::Button* button_move_down = nullptr;
    Gtk::Button* button_move_left = nullptr;
    Gtk::Button* button_move_right = nullptr;
    Gtk::Entry* input_move = nullptr;

    // Inflation
    Gtk::Button* button_inflate_plus = nullptr;
    Gtk::Button* button_inflate_minus = nullptr;
    Gtk::Entry* input_inflate = nullptr;

    // Rotation
    Gtk::RadioButton* radio_coord = nullptr;
    Gtk::RadioButton* radio_shape = nullptr;
    Gtk::RadioButton* radio_viewport = nullptr;
    Gtk::Button* button_rotate_left = nullptr;
    Gtk::Button* button_rotate_right = nullptr;
    Gtk::Entry* input_angle = nullptr;
    Gtk::Entry* input_rotate_x = nullptr;
    Gtk::Entry* input_rotate_y = nullptr;
    Gtk::Entry* input_rotate_z = nullptr;
  
protected:
    Shape get_shape() {
        return shapes[combobox_shapes->get_active_row_number()];
    }
};

}  // namespace Control

#endif  // CONTROL_SHAPES_H