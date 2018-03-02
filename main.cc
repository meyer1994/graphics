#include <gtkmm.h>

#include "components/controls_view.h"

int main(int argc, char* argv[]) {

	auto app = Gtk::Application::create(argc, argv, "example");

	Gtk::Window window;
	window.set_border_width(10);

	Components::ControlsView controls;

	window.add(controls);
	window.show_all_children();

	return app->run(window);
}

