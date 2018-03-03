#ifndef LINE_H
#define LINE_H

#include "drawable.h"

class Line : public Drawable {
public:
	Line(const Point& a, const Point& b);
	~Line();
};

#endif  // LINE_H