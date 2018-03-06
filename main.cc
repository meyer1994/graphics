#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

#include "src/mode/draw.h"
#include "src/mode/movement.h"
#include "src/mode/display_file.h"


void connect_draw(Glib::RefPtr<Gtk::Builder>& builder, DisplayFile& df) {
    Gtk::DrawingArea* drawing_area = nullptr;
    builder->get_widget("drawing_area", drawing_area);

    auto binded = sigc::bind(&draw, df);
    drawing_area->signal_draw().connect(binded);
}

void connect_buttons(Glib::RefPtr<Gtk::Builder>& builder) {

}

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");

    auto builder = Gtk::Builder::create();
    builder->add_from_file("src/view/main_window.glade");

    Gtk::Window* window = nullptr;
    builder->get_widget("window_main", window);

    DisplayFile display_file;

    connect_draw(builder, display_file);

	app->run(*window);

    delete window;
    return 0;
}
