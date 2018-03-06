#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include <gtkmm/drawingarea.h>

#include "src/mode/draw.h"
#include "src/mode/movement.h"
#include "src/mode/display_file.h"


void connect_draw(Glib::RefPtr<Gtk::Builder>& builder, DisplayFile* df) {
    Gtk::DrawingArea* drawing_area = nullptr;
    builder->get_widget("drawing_area", drawing_area);

    auto binded = sigc::bind(&draw, df);
    drawing_area->signal_draw().connect(binded);
}

void connect_buttons(Glib::RefPtr<Gtk::Builder>& builder, DisplayFile* df) {
    Gtk::DrawingArea* drawing_area = nullptr;
    builder->get_widget("drawing_area", drawing_area);

    Gtk::Button* button_up = nullptr;
    builder->get_widget("button_up", button_up);
    auto bind_up = sigc::bind(&move_up, df, drawing_area);
    button_up->signal_clicked().connect(bind_up);

    Gtk::Button* button_down = nullptr;
    builder->get_widget("button_down", button_down);
    auto bind_down = sigc::bind(&move_down, df, drawing_area);
    button_down->signal_clicked().connect(bind_down);

    Gtk::Button* button_left = nullptr;
    builder->get_widget("button_left", button_left);
    auto bind_left = sigc::bind(&move_left, df, drawing_area);
    button_left->signal_clicked().connect(bind_left);

    Gtk::Button* button_right = nullptr;
    builder->get_widget("button_right", button_right);
    auto bind_right = sigc::bind(&move_right, df, drawing_area);
    button_right->signal_clicked().connect(bind_right);
}

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");

    auto builder = Gtk::Builder::create();
    builder->add_from_file("src/view/main_window.glade");

    Gtk::Window* window = nullptr;
    builder->get_widget("window_main", window);

    DisplayFile display_file;

    connect_draw(builder, &display_file);
    connect_buttons(builder, &display_file);

	return app->run(*window);
}
