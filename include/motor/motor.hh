#pragma once

#include "image/image.hh"
#include "scene/scene.hh"

class Motor {
public:
    Motor(Scene scene);

    Image render();
    Vector3 determineRay(const int i, const int j);
    std::list<Vector3> determineRays(const int i, const int j);
    Color* determineColor(std::list<Vector3> rays);

    Color* castRay(const Point3 &c, const Vector3 &vect, const int depth = 0);

private:
    Scene scene_;
    double width_;
    double height_;
    double ratio_;
    int width_pixels_;
    int height_pixels_;

    Vector3 forward;
    Vector3 right;
    Vector3 up;
};
