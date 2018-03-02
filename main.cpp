#include <gtkmm.h>
#include <iostream>
#include <string>

void quit(Gtk::Window* data) {
	delete data;
}

void increment(int* counter, Gtk::Label* label) {
	*counter += 1;
	label->set_label(std::to_string(*counter));
}

int main(int argc, char* argv[]) {

	auto app = Gtk::Application::create(argc, argv, "example");
	
	int counter = 0;

	Gtk::Window window;
	window.set_title("counter");
	window.set_border_width(10);
	window.set_default_size(200, 200);
	window.signal_hide().connect(sigc::bind(&quit, &window));

	Gtk::Label* title = new Gtk::Label("Pressed:");
	Gtk::Label* times = new Gtk::Label(std::to_string(counter));

	Gtk::Button* button = new Gtk::Button("click me");
	button->signal_clicked().connect(sigc::bind(&increment, &counter, times));

	Gtk::Box* box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
	box->pack_start(*title, Gtk::PACK_SHRINK);
	box->pack_start(*times, Gtk::PACK_SHRINK);
	box->pack_start(*button, Gtk::PACK_SHRINK);

	title->show();
	times->show();
	button->show();

	window.add(*box);

	box->show();

	return app->run(window);
}

