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
#include <gtkmm/checkbutton.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/imagemenuitem.h>

#include "../mode/shapes/dot.h"
#include "../mode/shapes/line.h"
#include "../mode/shapes/point.h"
#include "../mode/shapes/shape.h"
#include "../mode/shapes/polygon.h"
#include "../mode/shapes/base_shape.h"
#include "../mode/shapes/bezier_curve.h"
#include "../mode/shapes/surface_bezier.h"
#include "../mode/shapes/surface_spline.h"
#include "../mode/viewport.h"

namespace Control {

class Dialog {
public:
    Dialog(Glib::RefPtr<Gtk::Builder>& b, Mode::Viewport& viewport)
    : viewport(viewport) {

        b->get_widget("dialog_input", dialog_input);

        // Menu item
        b->get_widget("menu_item_new", menu_item_new);

        // Buttons
        b->get_widget("button_finish", button_finish);
        b->get_widget("button_cancel", button_cancel);
        b->get_widget("button_add_point", button_add_point);
        b->get_widget("checkbox_filled", checkbox_filled);

        // Radio buttons
        b->get_widget("radio_dot", radio_dot);
        b->get_widget("radio_line", radio_line);
        b->get_widget("radio_polygon", radio_polygon);
        b->get_widget("radio_bezier_curve", radio_bezier_curve);
        b->get_widget("radio_bspline_curve", radio_bspline_curve);
        b->get_widget("radio_bezier_surface", radio_bezier_surface);
        b->get_widget("radio_spline_surface", radio_spline_surface);

        // Inputs
        b->get_widget("text_input_name", text_input_name);
        b->get_widget("text_input_x", text_input_x);
        b->get_widget("text_input_y", text_input_y);
        b->get_widget("text_input_z", text_input_z);

        // Combo box
        b->get_widget("combobox_shapes", combobox_shapes);
        b->get_widget("box_points_added", box_points_added);

        connect_buttons();
    }

    ~Dialog() {
        delete dialog_input;
        clear_labels();
    }

protected:
    // Hold created points
    std::vector<Point> points_buffer;

    // Hold created points labels
    std::vector<Gtk::Label*> points_labels_buffer;

    // Shapes reference
    Mode::Viewport& viewport;

    // Top-level dialog
    Gtk::Dialog* dialog_input = nullptr;

    // Combobox
    Gtk::ComboBoxText* combobox_shapes = nullptr;

    // Menu items
    Gtk::ImageMenuItem* menu_item_new = nullptr;
    Gtk::ImageMenuItem* menu_item_open = nullptr;
    Gtk::ImageMenuItem* menu_item_save = nullptr;
    Gtk::ImageMenuItem* menu_item_save_as = nullptr;

    // Buttons
    Gtk::Button* button_finish = nullptr;
    Gtk::Button* button_cancel = nullptr;
    Gtk::Button* button_add_point = nullptr;
    Gtk::CheckButton* checkbox_filled = nullptr;

    // Radio buttons
    Gtk::RadioButton* radio_dot = nullptr;
    Gtk::RadioButton* radio_line = nullptr;
    Gtk::RadioButton* radio_polygon = nullptr;
    Gtk::RadioButton* radio_bezier_curve = nullptr;
    Gtk::RadioButton* radio_bspline_curve = nullptr;
    Gtk::RadioButton* radio_spline_surface = nullptr;
    Gtk::RadioButton* radio_bezier_surface = nullptr;

    // Text entries
    Gtk::Entry* text_input_name = nullptr;
    Gtk::Entry* text_input_x = nullptr;
    Gtk::Entry* text_input_y = nullptr;
    Gtk::Entry* text_input_z = nullptr;

    // Hold labels of the points added
    Gtk::Box* box_points_added = nullptr;

    void connect_buttons() {
        button_finish
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::finish));
        button_cancel
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::cancel));
        button_add_point
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &Control::Dialog::add_point));
        menu_item_new
            ->signal_activate()
            .connect(sigc::mem_fun(*dialog_input, &Gtk::Dialog::show));
    }

    const Point get_point() {
        // Get text input
        const std::string sx = text_input_x->get_text();
        const std::string sy = text_input_y->get_text();
        const std::string sz = text_input_z->get_text();

        // Convert to double
        const double x = std::stod(sx);
        const double y = std::stod(sy);
        const double z = std::stod(sz);

        return Point(x, y, z);
    }

    const bool add_shape() {
        // No points no shape
        if (points_buffer.empty()) {
            return false;
        }

        // No name no shape
        std::string name = text_input_name->get_text();
        if (name.empty()) {
            return false;
        }

        const int buff_size = points_buffer.size();

        // Dot
        if (buff_size >= 1 && radio_dot->get_active()) {
            const Point p = points_buffer[0];
            viewport.shapes.push_back(new Dot(p, name));
        }

        // Line
        if (buff_size >= 2 && radio_line->get_active()) {
            const Point a = points_buffer[0];
            const Point b = points_buffer[1];
            viewport.shapes.push_back(new Line(a, b, name));
        }

        // Polygon
        if (buff_size > 2 && radio_polygon->get_active()) {
            Polygon* p = new Polygon(points_buffer, name);
            p->filled = checkbox_filled->get_active();
            viewport.shapes.push_back(p);
        }

        // Bezier curve
        if (buff_size % 3 - 1 == 0 && radio_bezier_curve->get_active()) {
            BezierCurve* bc = new BezierCurve(points_buffer, 0.05, name);
            viewport.shapes.push_back(bc);
        }

        // b-spline
        if (buff_size > 3 && radio_bspline_curve->get_active()) {
            Spline* bc = new Spline(points_buffer, 0.05, name);
            viewport.shapes.push_back(bc);
        }

        // Bezier surface
        if (buff_size == 16 && radio_bezier_curve->get_active()) {
            std::vector<std::vector<Point>> v(4, std::vector<Point>());
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    v[i].push_back(points_buffer[(i*4)+j]);
                }
            }
            SurfaceBezier* bc = new SurfaceBezier(v, 0.05, name);
            viewport.shapes.push_back(bc);
        }

        // Spline surface
        // if (buff_size >= 16 && radio_bezier_curve->get_active()) {
        //     BezierCurve* bc = new BezierCurve(points_buffer, 0.05, name);
        //     viewport.shapes.push_back(bc);
        // }

        // Add shape name to combo box
        combobox_shapes->append(name);

        // Redraw drawing area
        viewport.draw();

        return true;
    }

    void cancel() {
        // Clear everything
        text_input_name->set_text("");
        text_input_x->set_text("");
        text_input_y->set_text("");
        text_input_z->set_text("");
        clear_labels();

        // Hide dialog
        dialog_input->hide();

        // Clear points
        points_buffer.clear();
    }

    void finish() {
        if (add_shape()) {
            cancel();
        }
    }

    void add_point() {
        try {
            // Get point
            const Point p = get_point();
            points_buffer.push_back(p);

            // Clear text inputs
            text_input_x->set_text("");
            text_input_y->set_text("");
            text_input_z->set_text("");

            // Update text view
            update_added_points(p);
        } catch (std::exception& e) {
            // Nothing
        }
    }

    void clear_labels() {
        for (int i = 0; i < points_labels_buffer.size(); i++) {
            box_points_added->remove(*points_labels_buffer[i]);
            delete points_labels_buffer[i];
        }
        points_labels_buffer.clear();
        points_labels_buffer.shrink_to_fit();
    }

    void update_added_points(const Point& p) {
        Gtk::Label* l = new Gtk::Label(p.to_string());
        points_labels_buffer.push_back(l);
        box_points_added->add(*l);
        l->show();
    }
};

}  // namespace Control

#endif  // CONTROL_DIALOG_H
