#include "light/point_light.hh"

PointLight::PointLight(Point3 position, double intensity)
: position_(position), intensity_(intensity)
{
}

double PointLight::getIntensity() const
{
    return intensity_;
}

const Point3& PointLight::getPosition() const
{
    return position_;
}
