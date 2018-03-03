#include <gtkmm.h>

#include "src/view/canvas.h"
#include "src/shapes/polygon.h"

int main(int argc, char* argv[]) {

	auto app = Gtk::Application::create(argc, argv, "example");

	Gtk::Window window;
	window.set_border_width(10);

	View::Canvas canvas;

	window.add(canvas);
	window.show_all_children();

	// square
	Shape::Polygon square(std::vector<Point> {
		Point(10, 10),
		Point(110, 10),
		Point(110, 110),
		Point(10, 110)
	});

	canvas.queue.push_back(square);

	return app->run(window);
}

