#include <gtkmm/window.h>
#include <gtkmm/application.h>

#include "src/control.h"
#include "src/view/view.h"
#include "src/mode/display_file.h"



int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");

    View view("src/view/main_window.glade");
    Gtk::Window* window = nullptr;
    view.builder->get_widget("window_main", window);

    DisplayFile display_file;

    Control control(view, display_file);

	return app->run(*window);
}
