#include "geometry/point.hh"
#include <iostream>

Point3::Point3(double x, double y, double z)
: x_(x), y_(y), z_(z)
{
}

Point3::Point3(const Point3& p)
: x_(p.getX()), y_(p.getY()), z_(p.getZ())
{
}

double Point3::getX() const
{
    return x_;
}

double Point3::getY() const
{
    return y_;
}

double Point3::getZ() const
{
    return z_;
}

Point3 Point3::operator+(const Point3 &p) const
{
    return Point3(x_ + p.getX(), y_ + p.getY(), z_ + p.getZ());
}

Point3 Point3::operator-(const Point3 &p) const
{
    return Point3(x_ - p.getX(), y_ - p.getY(), z_ - p.getZ());
}

Point3 Point3::operator*(const double &l) const
{
    return Point3(x_ * l, y_ * l, z_ * l);
}

Point3 Point3::operator*(const Matrix &m) const
{
    return Point3(m.get(0, 0) * x_ + m.get(0, 1) * y_ + m.get(0, 2) * z_,
                  m.get(1, 0) * x_ + m.get(1, 1) * y_ + m.get(1, 2) * z_,
                  m.get(2, 0) * x_ + m.get(2, 1) * y_ + m.get(2, 2) * z_);
}

Point3 Point3::operator/(const double &l) const
{
    return Point3(x_ / l, y_ / l, z_ / l);
}

Point3 Point3::operator=(const Point3 &p)
{
    x_ = p.getX();
    y_ = p.getY();
    z_ = p.getZ();

    return *this;
}

std::ostream& operator<<(std::ostream &out, const Point3 &p)
{
    return out << "Point: (" << p.getX() << "," << p.getY() << "," << p.getZ() << ")";
}
