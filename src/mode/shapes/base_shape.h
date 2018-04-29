#ifndef BASE_SHAPE_H
#define BASE_SHAPE_H

#include <string>
#include <utility>

#include "point.h"
#include "vector.h"

enum class ShapeType { Dot, Line, Polygon, BezierCurve, Spline, Polyhedron };

class BaseShape {
public:
    BaseShape() : medium(0, 0, 0), name("base_shape") {}
    
    BaseShape(std::string name) : medium(0, 0, 0), name(name) {}

    virtual ~BaseShape() {}

	virtual void rotate(const double x, const double y, const double z) = 0;

	virtual void rotate(const double angle, const Vector& v) = 0;

	virtual void scale(const double ratio) = 0;

	virtual void inflate(const double ratio) = 0;

	virtual void translate(const double x, const double y, const double z) = 0;

    virtual void transform(const Matrix& m) = 0;

    virtual void w_transform(const Matrix& m) = 0;

    virtual const ShapeType type() const = 0;

    Point medium;
    std::string name;
};

#endif  // BASE_SHAPE_H