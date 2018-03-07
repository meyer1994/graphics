#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include "../view/view.h"
#include "../mode/drawable.h"
#include "draw.h"
#include "movement.h"
#include "zoom.h"

class Control {
public:
    Control(View& view) : view(view) {
        Drawable d(std::vector<Point> {
            Point(0, 0),
            Point(100, 0),
            Point(100, 100),
            Point(0, 100)
        });
        shapes.push_back(d);

        connect_draw();
        connect_buttons();
    }
    ~Control() {}

    View& view;
    std::vector<Drawable> shapes;

protected:
    void connect_draw() {
        auto binded = sigc::bind(&draw, &shapes);
        view.window.drawing_area->signal_draw().connect(binded);
    }

    void connect_buttons() {
        auto bind_up = sigc::bind(&move_up, &shapes, &view);
        view.window.button_up->signal_clicked().connect(bind_up);

        auto bind_down = sigc::bind(&move_down, &shapes, &view);
        view.window.button_down->signal_clicked().connect(bind_down);

        auto bind_left = sigc::bind(&move_left, &shapes, &view);
        view.window.button_left->signal_clicked().connect(bind_left);

        auto bind_right = sigc::bind(&move_right, &shapes, &view);
        view.window.button_right->signal_clicked().connect(bind_right);

        auto bind_in = sigc::bind(&zoom_in, &shapes, &view);
        view.window.button_in->signal_clicked().connect(bind_in);

        auto bind_out = sigc::bind(&zoom_out, &shapes, &view);
        view.window.button_out->signal_clicked().connect(bind_out);
    }
    
};

#endif  // CONTROL_H