#pragma once

#include "geometry/matrix.hh"
#include "geometry/point.hh"

class Vector3 {
public:
    Vector3(Point3 p);
    Vector3(double x, double y, double z);

    const Point3& getP() const;

    double getAngle(const Vector3 &vect) const;
    double getNorm() const;

    Vector3 normalize();
    Vector3 normalize() const;

    Vector3 cross(const Vector3 &vect) const;

    Vector3 operator+(const Vector3 &vect) const;
    Vector3 operator-(const Vector3 &vect) const;
    Vector3 operator*(const Matrix &m) const;
    Vector3 operator*(const double &l) const;
    Vector3 operator/(const double &l) const;

    double operator*(const Vector3 &vect) const;

    friend std::ostream& operator<<(std::ostream &out, const Vector3 &vect);
private:
    Point3 p_;
};
