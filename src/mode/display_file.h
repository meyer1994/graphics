#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <vector>
#include "drawable.h"

class DisplayFile {
public:
	DisplayFile()
	: shapes_list(),
	  root_point{0, 0},
	  step_size(10),
	  zoom_level(0) {

        // Dummy line
        Point c1 {0, 0};
        Point c2 {110, 110};
        Drawable d(std::vector<Point> {c1, c2});
        shapes_list.push_back(d);
	}
	
	std::vector<Drawable> shapes_list;
	Point root_point;
	double step_size;
	double zoom_level;

};

#endif  // DISPLAY_FILE_H