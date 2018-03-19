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

#include "../mode/shape.h"

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

        connect_buttons();
    }

    ~Shapes() {}

    void move_up() {
        Shape& s = get_shape();
        double move = get_move_input();
        s.translate(0, move);
        drawing_area->queue_draw();
    }

    void move_down() {
        Shape& s = get_shape();
        double move = get_move_input();
        s.translate(0, -move);
        drawing_area->queue_draw();
    }

    void move_left() {
        Shape& s = get_shape();
        double move = get_move_input();
        s.translate(-move, 0);
        drawing_area->queue_draw();
    }

    void move_right() {
        Shape& s = get_shape();
        double move = get_move_input();
        s.translate(move, 0);
        drawing_area->queue_draw();
    }

    void inflate() {
    	Shape& s = get_shape();
    	double ratio = get_inflate_input();
    	s.inflate(ratio);
        drawing_area->queue_draw();
    }

    void deflate() {
    	Shape& s = get_shape();
    	double ratio = get_inflate_input();
    	s.inflate(1/ratio);
        drawing_area->queue_draw();
    }

    void rotate_left() {
    	Shape& s = get_shape();
    	double angle = get_rotate_input();
    	s.rotate(angle);
        drawing_area->queue_draw();
    }

    void rotate_right() {
    	Shape& s = get_shape();
    	double angle = get_rotate_input();
    	s.rotate(-angle);
        drawing_area->queue_draw();
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
    Shape& get_shape() {
        int index = combobox_shapes->get_active_row_number();
        if (index > 0) {
            return shapes[index];
        }
        return shapes[0];
    }

    void connect_buttons() {
        button_move_up
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::move_up));

        button_move_down
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::move_down));

        button_move_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::move_left));

        button_move_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::move_right));

        button_inflate_plus
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::inflate));

        button_inflate_minus
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::deflate));


        button_rotate_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::rotate_left));

        button_rotate_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Shapes::rotate_right));
        // radio_shape
        //     ->signal_clicked()
        //     .connect(sigc::mem_fun(*this, &Shapes::deflate));
        // radio_coord
        //     ->signal_clicked()
        //     .connect(sigc::mem_fun(*this, &Shapes::deflate));
        // radio_viewport
        //     ->signal_clicked()
        //     .connect(sigc::mem_fun(*this, &Shapes::deflate));




    }

    double get_move_input() const {
        double move_size = 10;
        try {
            std::string move_input = input_move->get_text();
            move_size = std::stod(move_input);
        } catch (std::exception& e) {
            // Nothing
        }
        return move_size;
    }

    double get_inflate_input() const {
        double inflate_size = 1.5;
        try {
            std::string inflate_input = input_inflate->get_text();
            inflate_size = std::stod(inflate_input);
        } catch (std::exception& e) {
            // Nothing
        }
        return inflate_size;
    }

    double get_rotate_input() const {
        double angle_value = 30;
        try {
            std::string angle_input = input_angle->get_text();
            angle_value = std::stod(angle_input);
        } catch (std::exception& e) {
            // Nothing
        }
        return angle_value;
    }



};

}  // namespace Control

#endif  // CONTROL_SHAPES_H
