#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
	Window() {}

	Window(double xmx, double ymx, double xmn, double ymn) {
		xmax = xmx;
		ymax = ymx;
		xmin = xmn;
		ymin = ymn;
	}

	~Window() {}
	
	double xmax;
	double ymax;
	double xmin;
	double ymin;
};

#endif  // WINDOW_H