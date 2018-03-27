#ifndef CONTROL_FILE_CHOOSER_DIALOG_H
#define CONTROL_FILE_CHOOSER_DIALOG_H

#include <vector>
#include <string>
#include <exception>

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/filechooserdialog.h>

#include "../mode/objdescriptor.h"

namespace Control {

class FileDialog {
public:
    FileDialog(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s)
    : shapes(s) {

        b->get_widget("drawing_area", drawing_area);
        b->get_widget("dialog_file_chooser", dialog_file_chooser);

        dialog_file_chooser->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog_file_chooser->add_button("_Open", Gtk::RESPONSE_OK);
    }

    ~FileDialog() {
        delete dialog_file_chooser;
    }

    void on_file_clicked() {
        //Show the dialog and wait for a user response:
        int result = dialog_file_chooser->run();

        //Handle the response:
        switch(result) {
            case(Gtk::RESPONSE_OK):
            {
                std::string filename = dialog_file_chooser->get_filename();
                std::cout << shapes.size() << std::endl;
                ObjDescriptor obj(shapes);
                obj.read(filename);
                drawing_area->queue_draw();
                std::cout << shapes.size() << std::endl;
                dialog_file_chooser->hide();
                break;
            }
            case(Gtk::RESPONSE_CANCEL):
            {
                dialog_file_chooser->hide();
                break;
            }
        }
    }

    // Shapes reference
    std::vector<Shape>& shapes;

    // Top-level dialog
    Gtk::FileChooserDialog* dialog_file_chooser = nullptr;

    // Drawin area to update when adding new shapes
    Gtk::DrawingArea* drawing_area = nullptr;
};

}  // namespace Control

#endif  // CONTROL_FILE_CHOOSER_DIALOG_H