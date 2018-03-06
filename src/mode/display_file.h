#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <vector>
#include "drawable.h"

class DisplayFile {
public:
	DisplayFile()
	: shapes_list(),
	  zoom_level(0) {

        // Dummy line
        Point c1 {0, 0};
        Point c2 {100, 0};
        Point c3 {100, 100};
        Point c4 {0, 100};
        Drawable d(std::vector<Point> {c1, c2, c3, c4});
        shapes_list.push_back(d);
	}
	
	std::vector<Drawable> shapes_list;
	double zoom_level;

};

#endif  // DISPLAY_FILE_H