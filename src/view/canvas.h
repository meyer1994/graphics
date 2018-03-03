#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <gtkmm/drawingarea.h>
#include "../shapes/drawable.h"

namespace View {

class Canvas : public Gtk::DrawingArea {
public:
	Canvas();
	~Canvas();

	std::vector<Drawable> queue;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
	void draw_shape(const Cairo::RefPtr<Cairo::Context>& cr, const Drawable& draw);
};

}  // namespace View

#endif  // CANVAS_H