#include <iostream>

#include <gtkmm/application.h>
#include <gtkmm/builder.h>

#include "src/control/main.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");
    auto builder = Gtk::Builder::create_from_file("src/view/layout.glade");
    
    Control::Main c(builder);

	return app->run(*c.window_main);
}
