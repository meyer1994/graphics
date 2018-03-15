#ifndef CONTROL_DIALOG_H
#define CONTROL_DIALOG_H

#include <vector>
#include <string>
#include <exception>

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/textview.h>
#include <gtkmm/drawingarea.h>

#include "../mode/dot.h"
#include "../mode/line.h"
#include "../mode/point.h"
#include "../mode/shape.h"
#include "../mode/polygon.h"

namespace Control {

class Dialog {
public:
    Dialog(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s, std::vector<Gtk::Label*>& a)
    : shapes(s),
      shapes_added(a) {
        b->get_widget("dialog_input", dialog_input);
        b->get_widget("list_shapes", list_shapes);
        b->get_widget("button_add_shape", button_add_shape);
        b->get_widget("button_finish", button_finish);
        b->get_widget("button_cancel", button_cancel);
        b->get_widget("button_add_point", button_add_point);
        b->get_widget("text_input_name", text_input_name);
        b->get_widget("text_input_x", text_input_x);
        b->get_widget("text_input_y", text_input_y);
        b->get_widget("text_points_added", text_points_added);
        b->get_widget("drawing_area", drawing_area);

        connect_buttons();
    }

    ~Dialog() {
        delete dialog_input;
    }

    void add_point() {
        try {
            // Get point
            Point p = get_point();
            points_added.push_back(p);

            // Clear text inputs
            text_input_x->set_text("");
            text_input_y->set_text("");

            // Update text view
            update_added_points(p);
        } catch (std::exception& e) {
            // Nothing
        }
    }

    void add_shape() {
        if (points_added.size() == 0) {
            return;
        }

        // Dot
        if (points_added.size() == 1) {
            Point p = points_added[0];
            shapes.push_back(Dot(p[0], p[1]));
        }

        // Line
        if (points_added.size() == 2) {
            Point a = points_added[0];
            Point b = points_added[1];
            shapes.push_back(Line(a, b));
        }

        // Polygon
        if (points_added.size() > 2) {
            shapes.push_back(Polygon(points_added));
        }

        // Redraw drawing area
        drawing_area->queue_draw();

        // Add label to list
        std::string name = text_input_name->get_text();
        Gtk::Label* l = new Gtk::Label(name);
        shapes_added.push_back(l);
        list_shapes->add(*l);
        l->show();
    }

    void cancel() {
        // Clear everything
        text_input_name->set_text("");
        text_input_x->set_text("");
        text_input_y->set_text("");
        text_points_added->get_buffer()->set_text("");

        // Hide dialog
        dialog_input->hide();

        // Clear points
        points_added.clear();
    }

    void finish() {
        add_shape();
        cancel();
    }

    std::vector<Point> points_added;
    std::vector<Shape>& shapes;

    std::vector<Gtk::Label*>& shapes_added;

    Gtk::Box* list_shapes = nullptr;

    Gtk::Dialog* dialog_input = nullptr;

    Gtk::Button* button_add_shape = nullptr;
    Gtk::Button* button_finish = nullptr;
    Gtk::Button* button_cancel = nullptr;
    Gtk::Button* button_add_point = nullptr;

    Gtk::Entry* text_input_name = nullptr;
    Gtk::Entry* text_input_x = nullptr;
    Gtk::Entry* text_input_y = nullptr;

    Gtk::TextView* text_points_added = nullptr;

    Gtk::DrawingArea* drawing_area = nullptr;

protected:
    Point get_point() {
        // Get text input
        std::string sx = text_input_x->get_text();
        std::string sy = text_input_y->get_text();

        // Convert to double
        double x = std::stod(sx);
        double y = std::stod(sy);

        return Point(x, y);
    }

    void connect_buttons() {
        button_add_shape
            ->signal_clicked()
            .connect(sigc::mem_fun(*dialog_input, &Gtk::Dialog::show));
        button_finish
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::finish));
        button_cancel
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::cancel));
        button_add_point
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::add_point));
    }

    void update_added_points(Point& p) {
        std::string s = text_points_added->get_buffer()->get_text();
        s.append("\n");
        s.append(p.to_string());
        text_points_added->get_buffer()->set_text(s);
    }

};

}  // namespace Control

#endif  // CONTROL_DIALOG_H