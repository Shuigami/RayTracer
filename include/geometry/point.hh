#pragma once

#include "geometry/matrix.hh"
#include <ostream>

class Point3 {
public:
    Point3(double x, double y, double z);
    Point3(const Point3& p);

    double getX() const;
    double getY() const;
    double getZ() const;

    Point3 operator+(const Point3 &p) const;
    Point3 operator-(const Point3 &p) const;
    Point3 operator*(const Matrix &m) const;
    Point3 operator*(const double &l) const;
    Point3 operator/(const double &l) const;

    Point3 operator=(const Point3 &p);

    friend std::ostream& operator<<(std::ostream &out, const Point3 &p);
private:
    double x_;
    double y_;
    double z_;
};
