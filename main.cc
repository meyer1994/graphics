
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>

#include "src/control/control.h"

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");
    auto builder = Gtk::Builder::create_from_file("src/view/layout.glade");
    
    Control control(builder);

    Gtk::Window* win = nullptr;
    builder->get_widget("window_main", win);

	app->run(*win);

	return 0;
}
