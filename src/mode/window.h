#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
	Window(double xmax, double ymax, double xmin, double ymin)
	: xmax(xmax),
	  ymax(ymax),
	  xmin(xmin),
	  ymin(ymin) {}
	~Window() {}
	
	double xmax;
	double ymax;
	double xmin;
	double ymin;
};

#endif  // WINDOW_H