#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <string>
#include <exception>

#include <gtkmm/entry.h>
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

		// Movement controls
		b->get_widget("button_up", button_up);
		b->get_widget("button_down", button_down);
		b->get_widget("button_left", button_left);
		b->get_widget("button_right", button_right);
		b->get_widget("input_viewport_move", input_viewport_move);

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

	// Movement controls
	Gtk::Button* button_up = nullptr;
	Gtk::Button* button_left = nullptr;
	Gtk::Button* button_right = nullptr;
	Gtk::Button* button_down = nullptr;
	Gtk::Entry* input_viewport_move = nullptr;

	// Zoom controls
	Gtk::Button* button_in = nullptr;
	Gtk::Button* button_out = nullptr;
	Gtk::Entry* input_viewport_zoom = nullptr;

	void connect_buttons() {
		// Movement buttons
		button_up->signal_clicked().connect(
			[this]() {
				double x = get_x_movement();
				double y = get_y_movement();
				viewport.window.translate(x, y);
				viewport.draw();
			});
		button_down->signal_clicked().connect(
			[this]() {
				double x = get_x_movement();
				double y = get_y_movement();
				viewport.window.translate(-x, -y);
				viewport.draw();
			});
		button_left->signal_clicked().connect(
			[this]() {
				double x = get_x_movement();
				double y = get_y_movement();
				viewport.window.translate(-y, x);
				viewport.draw();
			});
		button_right->signal_clicked().connect(
			[this]() {
				double x = get_x_movement();
				double y = get_y_movement();
				viewport.window.translate(y, -x);
				viewport.draw();
			});

		// Zoom buttons
		button_in->signal_clicked().connect(
			[this]() {
				double zoom = get_zoom_input() / 100;
				viewport.window.inflate(1 - zoom);
				viewport.draw();
			});
		button_out->signal_clicked().connect(
			[this]() {
				double zoom = get_zoom_input() / 100;
				viewport.window.inflate(1 + zoom);
				viewport.draw();
			});

		// Rotation buttons
		button_rotate_left->signal_clicked().connect(
			[this]() {
				double angle = get_angle_input();
				Point medium = viewport.window.medium();
				viewport.window.rotate(-angle, medium);
				viewport.draw();
			});
		button_rotate_right->signal_clicked().connect(
			[this]() {
				double angle = get_angle_input();
				Point medium = viewport.window.medium();
				viewport.window.rotate(angle, medium);
				viewport.draw();
			});
	}

	double get_move_input() {
		double move_size = 10;
		try {
			std::string move_input = input_viewport_move->get_text();
			move_size = std::stod(move_input);

		} catch (std::exception& e) {
			// Nothing
		}
		return move_size;
	}

	double get_y_movement() {
		double move = get_move_input();
		double y_angle = viewport.window.y_angle();
		return std::cos(y_angle * _MATH_PI / 180) * move;
	}

	double get_x_movement() {
		double move = get_move_input();
		double y_angle = viewport.window.y_angle();
		return std::sin(y_angle * _MATH_PI / 180) * move;
	}

	double get_zoom_input() {
		double zoom_size = 10;
		try {
			std::string zoom_input = input_viewport_zoom->get_text();
			zoom_size = std::stod(zoom_input);

		} catch (std::exception& e) {
			// Nothing
		}
		return zoom_size;
	}

	double get_angle_input() {
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
