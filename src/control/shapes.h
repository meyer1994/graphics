#ifndef CONTROL_SHAPES_H
#define CONTROL_SHAPES_H

#include <string>
#include <stdexcept>

#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/viewport.h"
#include "../mode/shapes/point.h"
#include "../mode/shapes/shape.h"

namespace Control {

class Shapes {
public:
	Shapes(Glib::RefPtr<Gtk::Builder>& b, Mode::Viewport& viewport)
	: viewport(viewport) {

		// Get combo box
		b->get_widget("combobox_shapes", combobox_shapes);

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
		b->get_widget("radiobutton_shape_object_rotate", radio_shape);
		b->get_widget("radiobutton_shape_viewport_rotate", radio_viewport);
		b->get_widget("radiobutton_shape_point_rotate", radio_coord);
		b->get_widget("input_shape_rotation_x", input_rotate_x);
		b->get_widget("input_shape_rotation_y", input_rotate_y);
		b->get_widget("input_shape_rotation_z", input_rotate_z);
		b->get_widget("input_shape_rotation_angle", input_angle);
		b->get_widget("button_shape_rotate_left", button_rotate_left);
		b->get_widget("button_shape_rotate_right", button_rotate_right);

		// Clipping widgets
		b->get_widget("checkbox_shape_clipping", check_clipping);
		b->get_widget("radio_shape_clipping_cohen", radio_cohen);
		b->get_widget("radio_shape_clipping_liang", radio_liang);

		connect_buttons();
	}

	virtual ~Shapes() {}

protected:
	// Shapes to be drawn
	Mode::Viewport& viewport;

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

	// Clipping
	Gtk::CheckButton* check_clipping = nullptr;
	Gtk::RadioButton* radio_cohen = nullptr;
	Gtk::RadioButton* radio_liang = nullptr;

	void connect_buttons() {
		// Shape movement
		button_move_up
			->signal_clicked()
			.connect([this]() {
				const double m = get_move_input();
				move(0.0, m, 0.0);
				viewport.draw();
			});
		button_move_down
			->signal_clicked()
			.connect([this]() {
				const double m = get_move_input();
				move(0.0, -m, 0.0);
				viewport.draw();
			});
		button_move_left
			->signal_clicked()
			.connect([this]() {
				const double m = get_move_input();
				move(-m, 0.0, 0.0);
				viewport.draw();
			});
		button_move_right
			->signal_clicked()
			.connect([this]() {
				const double m = get_move_input();
				move(m, 0.0, 0.0);
				viewport.draw();
			});

		// Shape scaling
		button_inflate_plus
			->signal_clicked()
			.connect([this]() {
				const double ratio = get_inflate_input();
				inflate(ratio);
				viewport.draw();
			});
		button_inflate_minus
			->signal_clicked()
			.connect([this]() {
				const double ratio = get_inflate_input();
				inflate(1 / ratio);
				viewport.draw();
			});

		// Shape rotation
		button_rotate_left
			->signal_clicked()
			.connect([this]() {
				const double angle = get_rotate_input();
				rotate(angle);
				viewport.draw();
			});
		button_rotate_right
			->signal_clicked()
			.connect([this]() {
				const double angle = get_rotate_input();
				rotate(-angle);
				viewport.draw();
			});

		// Clipping
		check_clipping
			->signal_toggled()
			.connect([this]() {
				viewport.toggle_clipping();
				viewport.draw();
			});
		radio_liang
			->signal_toggled()
			.connect([this]() {
				viewport.clipping.line_method = LineClipMethod::LIANG_BARSKY;
				viewport.draw();
			});
		radio_cohen
			->signal_toggled()
			.connect([this]() {
				viewport.clipping.line_method = LineClipMethod::COHEN_SUTHERLAND;
				viewport.draw();
			});
	}

	BaseShape* get_shape() {
		int index = combobox_shapes->get_active_row_number();
		// get_active_row_number returns -1 when there is nothing selected
		if (index == -1) {
			throw std::runtime_error("No shape selected");
		}
		return viewport.shapes[index];
	}

	const Point get_point() {
		double x;
		double y;
		double z;
		try {
			x = std::stod(input_rotate_x->get_text());
			y = std::stod(input_rotate_y->get_text());
			z = std::stod(input_rotate_z->get_text());
		} catch (std::exception& e) {
			// pass
		}
		return Point(x, y, z);
	}

	const double get_move_input() const {
		double move_size = 10;
		try {
			std::string move_input = input_move->get_text();
			move_size = std::stod(move_input);
		} catch (std::exception& e) {
			// Nothing
		}
		return move_size;
	}

	const double get_inflate_input() const {
		double inflate_size = 1.5;
		try {
			std::string inflate_input = input_inflate->get_text();
			inflate_size = std::stod(inflate_input);
		} catch (std::exception& e) {
			// Nothing
		}
		return inflate_size;
	}

	const double get_rotate_input() const {
		double angle_value = 30;
		try {
			std::string angle_input = input_angle->get_text();
			angle_value = std::stod(angle_input);
		} catch (std::exception& e) {
			// Nothing
		}
		return angle_value;
	}

	const std::vector<double> get_rotation_axis() const {
		// Defaults
		double x = 0.0;
		double y = 0.0;
		double z = 1.0;

		// Convert everything
		try {
			std::string x_input = input_rotate_x->get_text();
			std::string y_input = input_rotate_y->get_text();
			std::string z_input = input_rotate_z->get_text();
			x = std::stod(x_input);
			y = std::stod(y_input);
			z = std::stod(z_input);
		} catch (const std::exception& e) {
			// Nothing
		}

		return {x, y, z};
	}

	void move(const double x, const double y, const double z) {
		try {
			BaseShape* s = get_shape();
			s->translate(x, y, z);
		} catch(std::exception& e) {
			// nothing
		}
	}

	void inflate(const double ratio) {
		try {
			BaseShape* s = get_shape();
			s->inflate(ratio);
		} catch(std::exception& e) {
			return;
		}
	}

	void rotate(const double angle) {
		try {
			BaseShape* s = get_shape();

			// Rotate to any point
			if(radio_coord->get_active()) {
				const std::vector<double> axis = get_rotation_axis();
				s->rotate(angle, axis);
			}

			// Rotate to center of window
			if(radio_viewport->get_active()) {
				s->rotate(angle, viewport.window.medium);
			}

			// Rotate from it's center
			if(radio_shape->get_active()) {
				const Matrix t0 = Transform::translate(-s->medium);
				const Matrix r  = Transform::rotatez(angle);
				const Matrix t1 = Transform::translate(s->medium);
				s->transform(t0 * r * t1);
			}

			viewport.draw();
		} catch(std::exception& e) {
			return;
		}
	}
};

}  // namespace Control

#endif  // CONTROL_SHAPES_H
