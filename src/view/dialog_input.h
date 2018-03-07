#ifndef DIALOG_INPUT_H
#define DIALOG_INPUT_H

#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <gtkmm/entry.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>

class DialogInput {
public:
    DialogInput() {
        builder = Gtk::Builder::create_from_file("src/view/dialog_input.glade");

        builder->get_widget("dialog_input", dialog_input);
        builder->get_widget("button_add_point", button_add_point);
        builder->get_widget("text_input_x", text_input_x);
        builder->get_widget("text_input_y", text_input_y);
        builder->get_widget("text_points_added", text_points_added);
        builder->get_widget("button_cancel", button_cancel);
        builder->get_widget("button_finish", button_finish);

        bind_buttons();
    }
    
    ~DialogInput() {
        delete dialog_input;
    }


    Gtk::Dialog* dialog_input;

protected:
    void bind_buttons() {
        button_add_point
            ->signal_clicked()
            .connect(sigc::mem_fun(*this, &DialogInput::add_point));
    }

    void add_point() {
        std::string x = text_input_x->get_text();
        std::string y = text_input_y->get_text();

        double xd;
        double yd;
        try {
            xd = std::stod(x);
            yd = std::stod(y);
            update_text_view(x, y);

            points.push_back(std::vector<double> {xd, yd});

            text_input_x->set_text("");
            text_input_y->set_text("");

        } catch(std::exception) {}
    }

    void update_text_view(std::string& x, std::string& y) {
        std::string current = text_points_added->get_buffer()->get_text();
        current += "(" + x + ", " + y + ")\n";
        text_points_added->get_buffer()->set_text(current);
    }

    std::vector<std::vector<double>> points;
    Gtk::Button* button_add_point;
    Gtk::Entry* text_input_x;
    Gtk::Entry* text_input_y;
    Gtk::TextView* text_points_added;
    Gtk::Button* button_cancel;
    Gtk::Button* button_finish;
    Glib::RefPtr<Gtk::Builder> builder;

};

#endif  // DIALOG_INPUT_H