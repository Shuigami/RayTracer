#pragma once

#include "geometry/point.hh"
class Light {
public:
    virtual double getIntensity() const = 0;
    virtual const Point3& getPosition() const = 0;
};
