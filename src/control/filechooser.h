#ifndef CONTROL_FILE_CHOOSER_DIALOG_H
#define CONTROL_FILE_CHOOSER_DIALOG_H

#include <vector>
#include <string>
#include <exception>

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/filechooserdialog.h>

#include "../mode/objdescriptor.h"

namespace Control {

class FileChooser {
public:
    FileChooser(Glib::RefPtr<Gtk::Builder>& b, std::vector<Shape>& s)
    : shapes(s),
      descriptor(s) {

        // Drawing area
        b->get_widget("drawing_area", drawing_area);

        // Dialog
        b->get_widget("dialog_file_chooser", dialog_file_chooser);

        // Menu items
        b->get_widget("menu_item_open", menu_item_open);
        b->get_widget("menu_item_save", menu_item_save);
        b->get_widget("menu_item_save_as", menu_item_save_as);

        // Default buttons
        dialog_file_chooser->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog_file_chooser->add_button("_Open", Gtk::RESPONSE_OK);

        // Combobox
        b->get_widget("combobox_shapes", combobox_shapes);

        connect_buttons();
    }

    ~FileChooser() {
        delete dialog_file_chooser;
    }

    void open() {
        dialog_file_chooser->set_action(Gtk::FILE_CHOOSER_ACTION_OPEN);

        //Show the dialog and wait for a user response:
        int result = dialog_file_chooser->run();

        //Handle the response:
        switch(result) {
            case(Gtk::RESPONSE_OK):
            {
                std::string filename = dialog_file_chooser->get_filename();
                descriptor.read(filename);
                combobox_shapes->remove_all();

                for (Shape& s : shapes) {
                    std::cout << s.name << std::endl;
                    combobox_shapes->append(s.name);
                }

                drawing_area->queue_draw();
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

    void save() {
        dialog_file_chooser->set_action(Gtk::FILE_CHOOSER_ACTION_SAVE);

        //Show the dialog and wait for a user response:
        int result = dialog_file_chooser->run();

        //Handle the response:
        switch(result) {
            case(Gtk::RESPONSE_OK):
            {
                std::string filename = dialog_file_chooser->get_current_name();
                descriptor.write(filename);
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

    // Obj descriptor
    ObjDescriptor descriptor;

    // Top-level dialog
    Gtk::FileChooserDialog* dialog_file_chooser = nullptr;

    // Drawin area to update when adding new shapes
    Gtk::DrawingArea* drawing_area = nullptr;

    // Combobox
    Gtk::ComboBoxText* combobox_shapes = nullptr;

    // Menu items
    Gtk::ImageMenuItem* menu_item_open = nullptr;
    Gtk::ImageMenuItem* menu_item_save = nullptr;
    Gtk::ImageMenuItem* menu_item_save_as = nullptr;

protected:
    void connect_buttons() {
        menu_item_open
            ->signal_activate()
            .connect(sigc::mem_fun(*this, &FileChooser::open));
        menu_item_save
            ->signal_activate()
            .connect(sigc::mem_fun(*this, &FileChooser::save));
    }
};

}  // namespace Control

#endif  // CONTROL_FILE_CHOOSER_DIALOG_H