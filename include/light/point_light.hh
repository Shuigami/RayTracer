#pragma once

#include "geometry/point.hh"
#include "light/light.hh"

class PointLight : public Light {
public:
    PointLight(Point3 position, double intensity);

    double getIntensity() const override;
    const Point3& getPosition() const override;

private:
    Point3 position_;
    double intensity_;
};
