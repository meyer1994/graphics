#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(double x, double y, double w = 1) : x(x), y(y), w(w) {}
    
    double x;
    double y;
    double w;
};

#endif  // POINT_H