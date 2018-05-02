#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <string>
#include <vector>
#include <exception>

#include <gtkmm/entry.h>
#include <gtkmm/scale.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>

#include "../mode/viewport.h"

namespace Control {

class Viewport {
public:
	Viewport(Glib::RefPtr<Gtk::Builder>& b, Mode::Viewport& viewport)
	: viewport(viewport) {

		// Rotation controls
		b->get_widget("input_angle", input_angle);
		b->get_widget("button_rotate_left", button_rotate_left);
		b->get_widget("button_rotate_right", button_rotate_right);
		b->get_widget("viewport_input_x", input_x);
		b->get_widget("viewport_input_y", input_y);
		b->get_widget("viewport_input_z", input_z);

		// Movement controls
		b->get_widget("button_up", button_up);
		b->get_widget("button_down", button_down);
		b->get_widget("button_left", button_left);
		b->get_widget("button_right", button_right);
		b->get_widget("input_viewport_move", input_viewport_move);

		// Perspective control
		b->get_widget("viewport_perspective_scale", scale_perspective);
		

		// Zoom controls
		b->get_widget("button_in", button_in);
		b->get_widget("button_out", button_out);
		b->get_widget("input_viewport_zoom", input_viewport_zoom);

		connect_buttons();
	}

	virtual ~Viewport() {}

protected:
	Mode::Viewport& viewport;

	// Rotation controls
	Gtk::Entry* input_angle = nullptr;
	Gtk::Button* button_rotate_right = nullptr;
	Gtk::Button* button_rotate_left = nullptr;
	Gtk::Entry* input_x = nullptr;
	Gtk::Entry* input_y = nullptr;
	Gtk::Entry* input_z = nullptr;

	// Movement controls
	Gtk::Button* button_up = nullptr;
	Gtk::Button* button_left = nullptr;
	Gtk::Button* button_right = nullptr;
	Gtk::Button* button_down = nullptr;
	Gtk::Entry* input_viewport_move = nullptr;

	// Perspective control
	Gtk::Scale* scale_perspective = nullptr;

	// Zoom controls
	Gtk::Button* button_in = nullptr;
	Gtk::Button* button_out = nullptr;
	Gtk::Entry* input_viewport_zoom = nullptr;

	void connect_buttons() {
		// Movement buttons
		button_up->signal_clicked().connect(
			[this]() {
				const double x = get_x_movement();
				const double y = get_y_movement();
				const Matrix t = Transform::translate(x, y, 0);
				viewport.window.transform(t);
				viewport.window.proj.transform(t);
				viewport.draw();
			});
		button_down->signal_clicked().connect(
			[this]() {
				const double x = get_x_movement();
				const double y = get_y_movement();
				const Matrix t = Transform::translate(-x, -y, 0);
				viewport.window.transform(t);
				viewport.window.proj.transform(t);
				viewport.draw();
			});
		button_left->signal_clicked().connect(
			[this]() {
				const double x = get_x_movement();
				const double y = get_y_movement();
				const Matrix t = Transform::translate(-y, x, 0);
				viewport.window.transform(t);
				viewport.window.proj.transform(t);
				viewport.draw();
			});
		button_right->signal_clicked().connect(
			[this]() {
				const double x = get_x_movement();
				const double y = get_y_movement();
				const Matrix t = Transform::translate(y, -x, 0);
				viewport.window.transform(t);
				viewport.window.proj.transform(t);
				viewport.draw();
			});

		// Zoom buttons
		button_in->signal_clicked().connect(
			[this]() {
				const double zoom = get_zoom_input() / 100;
				viewport.window.inflate(1 - zoom);
				viewport.draw();
			});
		button_out->signal_clicked().connect(
			[this]() {
				const double zoom = get_zoom_input() / 100;
				viewport.window.inflate(1 + zoom);
				viewport.draw();
			});

		// Perpective scale
		scale_perspective->signal_value_changed().connect(
			[this]() {
				double value = scale_perspective->get_value();
				value = Mode::Window::MIN_PERSPECTIVE * value;
				viewport.window.set_perspective(value);
				viewport.draw();
			});
		
		// Rotation buttons
		button_rotate_left->signal_clicked().connect(
			[this]() {
				const double angle = get_angle_input();
				const std::vector<double> axis = get_rotation_axis();
				viewport.window.rotate(-angle, axis);
				viewport.draw();
			});
		button_rotate_right->signal_clicked().connect(
			[this]() {
				const double angle = get_angle_input();
				const std::vector<double> axis = get_rotation_axis();
				viewport.window.rotate(angle, axis);
				viewport.draw();
			});
	}

	const double get_move_input() {
		double move_size = 10;
		try {
			std::string move_input = input_viewport_move->get_text();
			move_size = std::stod(move_input);

		} catch (std::exception& e) {
			// Nothing
		}
		return move_size;
	}

	const double get_y_movement() {
		const double move = get_move_input();
		const double y_angle = viewport.window.y_angle();
		return std::cos(y_angle * MATH_PI / 180) * move;
	}

	const double get_x_movement() {
		const double move = get_move_input();
		const double y_angle = viewport.window.y_angle();
		return std::sin(y_angle * MATH_PI / 180) * move;
	}

	const std::vector<double> get_rotation_axis() {
		// Defaults
		double x = 0.0;
		double y = 0.0;
		double z = 1.0;

		// Convert everything
		try {
			std::string x_input = input_x->get_text();
			std::string y_input = input_y->get_text();
			std::string z_input = input_z->get_text();
			x = std::stod(x_input);
			y = std::stod(y_input);
			z = std::stod(z_input);
			if (x == 0 && y == 0 && z == 0) {
				return {0, 0, 1};
			}
		} catch (const std::exception& e) {
			// Nothing
		}

		return {x, y, z};
	}

	const double get_zoom_input() {
		double zoom_size = 10;
		try {
			std::string zoom_input = input_viewport_zoom->get_text();
			zoom_size = std::stod(zoom_input);

		} catch (std::exception& e) {
			// Nothing
		}
		return zoom_size;
	}

	const double get_angle_input() {
		double angle = 30;
		try {
			std::string angle_input = input_angle->get_text();
			angle = std::stod(angle_input);
		} catch (std::exception& e) {
			// Nothing
		}
		return angle;
	}
};

}  // namespace Control


#endif  // CONTROL_VIEWPORT_H
