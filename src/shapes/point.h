#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point(float x, float y) : x_coord(x), y_coord(y) {}
    
	~Point() {}

	float x_coord;
	float y_coord;
};

#endif  // POINT_H