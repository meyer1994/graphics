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
#include <gtkmm/drawingarea.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/imagemenuitem.h>

#include "../mode/dot.h"
#include "../mode/line.h"
#include "../mode/point.h"
#include "../mode/shape.h"
#include "../mode/polygon.h"

namespace Control {

class Dialog {
public:
    /**
     * @brief Constructor.
     *
     * @param b Builder of the GTK application. Used to get all the widgets
     * that are related to this control.
     *
     * @param s Shapes vector. Will add new shapes to this vector.
     */
    Dialog(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s)
    : shapes(s) {

        b->get_widget("dialog_input", dialog_input);

        // Menu items
        b->get_widget("menu_item_new", menu_item_new);

        // Buttons
        b->get_widget("button_finish", button_finish);
        b->get_widget("button_cancel", button_cancel);
        b->get_widget("button_add_file", button_add_file);
        b->get_widget("button_add_point", button_add_point);

        // Inputs
        b->get_widget("text_input_name", text_input_name);
        b->get_widget("text_input_x", text_input_x);
        b->get_widget("text_input_y", text_input_y);


        b->get_widget("combobox_shapes", combobox_shapes);
        b->get_widget("box_points_added", box_points_added);

        // Drawing area
        b->get_widget("drawing_area", drawing_area);

        connect_buttons();
    }

    /**
     * @brief Destructor.
     *
     * @details The destructor for top-level widgets must be called explicitly.
     */
    ~Dialog() {
        delete dialog_input;
        clear_labels();
    }

    /**
     * @brief Add point to the point_buffer.
     *
     * @details Will only add the point if the inputs are correct numbers that
     * do not throw any kind of exception when passed to std::stod().
     */
    void add_point() {
        try {
            // Get point
            Point p = get_point();
            points_buffer.push_back(p);

            // Clear text inputs
            text_input_x->set_text("");
            text_input_y->set_text("");

            // Update text view
            update_added_points(p);
        } catch (std::exception& e) {
            // Nothing
        }
    }

    /**
     * @brief Adds new shape to shapes list and shapes combobox.
     *
     * @details If there is no points in points_buffer or no name has been set,
     * it won't do anything and it will return false.
     *
     * @return true if the shape was added. False otherwise.
     */
    bool add_shape() {
        // No points no shape
        if (points_buffer.empty()) {
            return false;
        }

        // No name no shape
        std::string name = text_input_name->get_text();
        if (name.empty()) {
            return false;
        }

        // Dot
        if (points_buffer.size() == 1) {
            Point p = points_buffer[0];
            shapes.push_back(Dot(p[0], p[1], name));
        }

        // Line
        if (points_buffer.size() == 2) {
            Point a = points_buffer[0];
            Point b = points_buffer[1];
            shapes.push_back(Line(a, b, name));
        }

        // Polygon
        if (points_buffer.size() > 2) {
            Polygon p(points_buffer, name);
            shapes.push_back(p);
        }

        // Add shape name to combobox
        combobox_shapes->append(name);

        // Redraw drawing area
        drawing_area->queue_draw();

        return true;
    }

    /**
     * @brief Cancel the adding of shape.
     *
     * @details Clear all the inputs and buffers and hides the dialog.
     */
    void cancel() {
        // Clear everything
        text_input_name->set_text("");
        text_input_x->set_text("");
        text_input_y->set_text("");
        clear_labels();

        // Hide dialog
        dialog_input->hide();

        // Clear points
        points_buffer.clear();
    }

    /**
     * @brief Add shape to memory and close the dialog.
     *
     * @details Will only close the dialog and add the shape if add_shape()
     * returns true.
     */
    void finish() {
        if (add_shape()) {
            cancel();
        }
    }

    // Hold created points
    std::vector<Point> points_buffer;

    // Hold created points labels
    std::vector<Gtk::Label*> points_labels_buffer;

    // Shapes reference
    std::vector<Shape>& shapes;

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
    Gtk::Button* button_add_file = nullptr;

    // Text entries
    Gtk::Entry* text_input_name = nullptr;
    Gtk::Entry* text_input_x = nullptr;
    Gtk::Entry* text_input_y = nullptr;

    // Hold labels of the points added
    Gtk::Box* box_points_added = nullptr;

    // Drawin area to update when adding new shapes
    Gtk::DrawingArea* drawing_area = nullptr;

protected:
    /**
     * @brief Get point.
     *
     * @details Gets the input from the user and convert to doubles.
     *
     * @return Point inputted by user.
     *
     * @throws std::invalid_argument If the input is "wrong". Wrong in the
     * sense of std::stod(double) not accepting it.
     */
    Point get_point() {
        // Get text input
        std::string sx = text_input_x->get_text();
        std::string sy = text_input_y->get_text();

        // Convert to double
        double x = std::stod(sx);
        double y = std::stod(sy);

        return Point(x, y);
    }

    /**
     * @brief Connects all buttons to it's functions.
     *
     * @details Will connect all the button signals to the methods they are
     * supposed to call.
     */
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

    /**
     * @brief Clear labels vector.
     *
     * @details The labels must be initialized with new when adding them to the
     * vector. So this method is just to clean them up. It also removes all the
     * references from the box_points_added widget by calling remove() on each
     * one of the labels in it.
     */
    void clear_labels() {
        for (int i = 0; i < points_labels_buffer.size(); i++) {
            box_points_added->remove(*points_labels_buffer[i]);
            delete points_labels_buffer[i];
        }
        points_labels_buffer.clear();
    }

    /**
     * @brief Updates box with added points.
     *
     * @details Simply adds a label with the point to the box.
     *
     * @param p Point to be added.
     */
    void update_added_points(Point& p) {
        Gtk::Label* l = new Gtk::Label(p.to_string());
        points_labels_buffer.push_back(l);
        box_points_added->add(*l);
        l->show();
    }

};

}  // namespace Control

#endif  // CONTROL_DIALOG_H
