#include <gtkmm/application.h>

#include "src/view/window.h"
#include "src/mode/display_file.h"
#include "src/mode/draw.h"
#include "src/mode/movement.h"


void connect_display_file(
    DisplayFile& display_file,
    Gtk::DrawingArea& drawing_area) {

    auto binded = sigc::bind(
        &draw,
        display_file);
    drawing_area.signal_draw().connect(binded);
}

// TODO
void connect_buttons(
    // Controls& controls,
    // DisplayFile& display_file,
    // Gtk::DrawingArea* drawing_area) {

    // auto bind_up = sigc::bind(
    //     &move_up,
    //     display_file,
    //     drawing_area);
    // controls.button_up.signal_clicked().connect(bind_up);

    // auto bind_down = sigc::bind(
    //     sigc::ptr_fun(&move_down),
    //     display_file,
    //     drawing_area);
    // controls.button_down.signal_clicked().connect(bind_down);

    // auto bind_left = sigc::bind(
    //     sigc::ptr_fun(&move_left),
    //     display_file,
    //     drawing_area);
    // controls.button_left.signal_clicked().connect(bind_left);

    // auto bind_right = sigc::bind(
    //     sigc::ptr_fun(&move_right),
    //     display_file,
    //     drawing_area);
    // controls.button_right.signal_clicked().connect(bind_right);
}

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.engine");

    Window window;
    DisplayFile display_file;

    connect_display_file(display_file, window.canvas);
    // connect_buttons(window.controls, display_file, window.canvas);

	return app->run(window);
}
