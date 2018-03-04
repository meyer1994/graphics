#include <gtkmm/application.h>

#include "src/view/window.h"

int main(int argc, char* argv[]) {

	auto app = Gtk::Application::create(argc, argv, "example");

	View::Window window;

	return app->run(window);
}
