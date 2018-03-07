#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <cstdlib>
#include <gtkmm/entry.h>
#include <gtkmm/builder.h>

class View {
public:
    View(std::string file) {
        builder = Gtk::Builder::create_from_file(file);
    }

    ~View() {}

    /**
     * @brief Get point input from input dialog.
     *
     * Will simply get the inputs from the text entrys in the dalog and return
     * a vector of doubles.
     *
     * @return Vector of 2 doubles, X and Y coordinates, in this order.
     */
    std::vector<double> get_point_input() {
        Gtk::Entry* entry_x = nullptr;
        Gtk::Entry* entry_y = nullptr;
        builder->get_widget("point_input_x", entry_x);
        builder->get_widget("point_input_y", entry_y);

        double x = std::stod(entry_x->get_text());
        double y = std::stod(entry_y->get_text());

        return std::vector<double> {x, y};
    }

    /**
     * @brief Get line points input from dialog.
     *
     * Same as get_point_input, but for the line.
     *
     * @return Vector of 2 vectors representing the 2 points of the line.
     */
    std::vector<std::vector<double>> get_line_input() {
        Gtk::Entry* entry_x1 = nullptr;
        Gtk::Entry* entry_y1 = nullptr;
        builder->get_widget("line_input_x1", entry_x1);
        builder->get_widget("line_input_y1", entry_y1);

        Gtk::Entry* entry_x2 = nullptr;
        Gtk::Entry* entry_y2 = nullptr;
        builder->get_widget("line_input_x2", entry_x2);
        builder->get_widget("line_input_y2", entry_y2);

        double x1 = std::stod(entry_x1->get_text());
        double y1 = std::stod(entry_y1->get_text());
        double x2 = std::stod(entry_x2->get_text());
        double y2 = std::stod(entry_y2->get_text());

        return std::vector<std::vector<double>> {
            std::vector<double> {x1, y1},
            std::vector<double> {x2, y2}
        };
    }
    
    Glib::RefPtr<Gtk::Builder> builder;
};

#endif  // VIEW_H