#include <gtkmm.h>

#include "src/view/canvas.h"
#include "src/shapes/line.h"

int main(int argc, char* argv[]) {

	auto app = Gtk::Application::create(argc, argv, "example");

	Gtk::Window window;
	window.set_border_width(10);

	View::Canvas canvas;

	window.add(canvas);
	window.show_all_children();

	Point a(0, 0);
	Point b(100, 100);
	Line line(a, b);

	canvas.queue.push_back(line);

	return app->run(window);
}

