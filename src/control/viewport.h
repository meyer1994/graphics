#ifndef CONTROL_VIEWPORT_H
#define CONTROL_VIEWPORT_H

#include <string>
#include <vector>
#include <exception>


#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/comboboxtext.h>

#include "../mode/shape.h"
#include "../mode/point.h"
#include "../mode/window.h"

namespace Control {

class Viewport {
public:
    Viewport(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s, Window& w)
    : window(w) {

        // Dummy shape
        s.push_back(Shape(std::vector<Point>{
            Point(0, 0),
            Point(50, 0),
            Point(50, 50)
        }));
        Gtk::ComboBoxText* c = nullptr;
        b->get_widget("combobox_shapes", c);
        c->append("teste");

        b->get_widget("drawing_area", drawing_area);

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

    ~Viewport() {}

    void move_up() {
        double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(x_move, y_move);
        drawing_area->queue_draw();
    }

    void move_down() {
        double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(-x_move, -y_move);
        drawing_area->queue_draw();
    }

    void move_left() {
		double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(-y_move, x_move);
        drawing_area->queue_draw();
    }

    void move_right() {
		double move = get_move_input();
        double y_angle = window.y_angle();
        double y_move = std::cos(y_angle * _MATH_PI / 180) * move;
        double x_move = std::sin(y_angle * _MATH_PI / 180) * move;
        window.rectangle.translate(y_move, -x_move);
        drawing_area->queue_draw();
    }

    void zoom_in() {
        double zoom = get_zoom_input() / 100;
        window.rectangle.inflate(1 - zoom);
        drawing_area->queue_draw();
    }

    void zoom_out() {
        double zoom = get_zoom_input() / 100;
        window.rectangle.inflate(1 + zoom);
        drawing_area->queue_draw();
    }

    void rotate_right() {
        double angle = get_angle_input();
        Point medium = window.rectangle.medium();
        window.rectangle.rotate(-angle, medium);
        drawing_area->queue_draw();
    }

    void rotate_left() {
        double angle = get_angle_input();
        Point medium = window.rectangle.medium();
        window.rectangle.rotate(angle, medium);
        drawing_area->queue_draw();
    }

    Window& window;

    Gtk::DrawingArea* drawing_area = nullptr;

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

protected:
    void connect_buttons() {
        button_up
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_up));

        button_down
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_down));

        button_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_left));

        button_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::move_right));

        button_in
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_in));

        button_out
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::zoom_out));

        button_rotate_left
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::rotate_left));

        button_rotate_right
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Viewport::rotate_right));
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
