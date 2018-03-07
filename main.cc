#include <gtkmm/application.h>
#include <iostream>

#include "src/control/control.h"
#include "src/view/view.h"

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");

    View view;
    view.window.window_main->show_all();
    view.window.window_main->set_default_size(350, 500);
    Control control(view);
    
	return app->run(*view.window.window_main);
}
