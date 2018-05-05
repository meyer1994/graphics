#ifndef SHAPE_COMPLEX_H
#define SHAPE_COMPLEX_H

#include <string>
#include <vector>

#include "shape.h"
#include "base_shape.h"

class ShapeComplex : public BaseShape {
public:
	ShapeComplex() : BaseShape("shapecomplex") {}

	ShapeComplex(std::string name) : BaseShape(name) {}

	ShapeComplex(std::initializer_list<Shape*> d)
	: BaseShape("shapecomplex"),
	  faces(d) {
	  	medium = calculate_medium();
	}

	ShapeComplex(std::vector<Shape*> faces, std::string name = "shapecomplex")
	: BaseShape(name),
	  faces(faces) {
	  	medium = calculate_medium();
	}

	virtual ~ShapeComplex() {
		for (Shape* s : faces) {
			delete s;
		}
		faces.clear();
	}

	virtual void rotate(const double x, const double y, const double z) {
		const Matrix rx = Transform::rotatex(x);
		const Matrix ry = Transform::rotatey(y);
		const Matrix rz = Transform::rotatez(z);

		const Matrix r = rx * ry * rz;
		transform(r);
	}

	virtual void rotate(const double angle, const Vector& v) {
		const Matrix r = Transform::rotate(angle, v);
		transform(r);
	}

	virtual void scale(double ratio) {
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		transform(s);
	}

	virtual void inflate(double ratio) {
		const Matrix t0 = Transform::translate(-medium);
		const Matrix s = Transform::scale(ratio, ratio, ratio);
		const Matrix t1 = Transform::translate(medium);
		transform(t0 * s * t1);
	}

    virtual void translate(double x, double y, double z) {
    	const Matrix t = Transform::translate(x, y, z);
    	transform(t);
    }

    virtual void transform(const Matrix& m) {
    	for (Shape* p : faces) {
    		p->transform(m);
    	}
    	medium.transform(m);
    }

    virtual void w_transform(const Matrix& m) {
    	for (Shape* p : faces) {
    		p->w_transform(m);
    	}
    }

	virtual const std::string to_string() const = 0;

	virtual const ShapeType type() const = 0;

	Point medium;
	std::string name;
	std::vector<Shape*> faces;

protected:
	virtual const Point calculate_medium() {
		Vector m(4, 0);
		for (Shape* p : faces) {
			m = m + p->medium;
		}
		m = m / faces.size();
		return Point(m);
	}
};

#endif  // SHAPE_COMPLEX_H
