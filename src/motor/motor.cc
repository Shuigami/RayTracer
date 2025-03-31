#include "motor/motor.hh"
#include "geometry/point.hh"
#include "geometry/vector.hh"
#include "image/color.hh"
#include "scene/camera.hh"
#include "scene/plane.hh"
#include "scene/scene.hh"
#include "logger/logger.hh"

#include <cmath>
#include <sys/types.h>

Motor::Motor(Scene scene)
: scene_(scene), width_(0), height_(0), ratio_(533.031282), width_pixels_(0), height_pixels_(0)
, forward(Vector3(0, 0, 0)), right(Vector3(0, 0, 0)), up(Vector3(0, 0, 0))
{
    width_ = 2 * scene_.getCamera().getZmin() * std::tan((scene_.getCamera().getAlpha() * M_PI / 180) / 2);
    height_ = 2 * scene_.getCamera().getZmin() * std::tan((scene_.getCamera().getBeta() * M_PI / 180) / 2);

    width_pixels_ = width_ * ratio_;
    height_pixels_ = height_ * ratio_;

    Logger::getInstance().log(Logger::Level::INFO, "Motor created.");
    Logger::getInstance().log(Logger::Level::INFO, "Width: " + std::to_string(width_) + " Height: " + std::to_string(height_));
    Logger::getInstance().log(Logger::Level::INFO, "Width pixels: " + std::to_string(width_pixels_) + " Height pixels: " + std::to_string(height_pixels_));

    const Camera &camera = scene_.getCamera();
    forward = Vector3(camera.getDirection() - camera.getCenter()).normalize();
    right = forward.cross(camera.getUp()).normalize();
    up = right.cross(forward).normalize();
}

Image Motor::render()
{
    std::list<Color*> pixels(width_pixels_ * height_pixels_, nullptr);

    const Point3 &c = scene_.getCamera().getCenter();

    Logger::getInstance().log(Logger::Level::INFO, "Rendering image...");

    int i = 0;
    int j = 0;
    for (auto p = pixels.begin(); p != pixels.end(); p++)
    {
        Vector3 vect = determineRay(i, j);
        *p = castRay(c, vect);

        // std::list<Vector3> rays = determineRays(i, j);
        // *p = determineColor(rays);

        i++;

        if (i < width_pixels_)
            continue;

        i = 0;
        j++;
    }

    Logger::getInstance().log(Logger::Level::INFO, "Image rendered.");

    Image img(height_pixels_, width_pixels_, pixels);
    return img;
}

Vector3 Motor::determineRay(const int i, const int j)
{
    double u = (2.0 * (i + 0.5) / width_pixels_ - 1.0) * width_ / 2.0;
    double v = (1.0 - 2.0 * (j + 0.5) / height_pixels_) * height_ / 2.0;

    Vector3 rayDirection = (forward * scene_.getCamera().getZmin() + right * u + up * v);

    return rayDirection;
}

std::list<Vector3> Motor::determineRays(const int i, const int j)
{
    std::list<Vector3> rays;

    double nb_ray = 10.0;
    double nb_ray_sqrt = sqrt(nb_ray);

    for (int k = 1; k <= nb_ray_sqrt; k++)
    {
        for (int l = 1; l <= nb_ray_sqrt; l++)
        {
            double u = (2.0 * (i + k / nb_ray_sqrt) / width_pixels_ - 1.0) * width_ / 2.0;
            double v = (1.0 - 2.0 * (j + l / nb_ray_sqrt) / height_pixels_) * height_ / 2.0;

            Vector3 rayDirection = (forward * scene_.getCamera().getZmin() + right * u + up * v);

            rays.push_back(rayDirection);
        }
    }

    return rays;
}

Color* Motor::determineColor(std::list<Vector3> rays)
{
    int r = 0;
    int g = 0;
    int b = 0;

    for (auto ray : rays)
    {
        Color *tmp = castRay(scene_.getCamera().getCenter(), ray);
        r += tmp->getR();
        g += tmp->getG();
        b += tmp->getB();
        delete tmp;
    }

    Color *color = new Color(r / rays.size(), g / rays.size(), b / rays.size());
    return color;
}

Color* Motor::castRay(const Point3 &c, const Vector3 &vect, const int depth)
{
    if (depth > 3)
        return new Color(0, 0, 0);

    Color *color = new Color(20, 20, 20);

    double t = -1;
    double smallest_t = -1;

    Object* closest_object = nullptr;
    Point3 closest_intersection = Point3(0, 0, 0);
    Vector3 closest_normal = Vector3(0, 0, 0);

    for (auto o : scene_.getObjects())
    {
        if (o->intersect(c, vect, t))
        {
            if (t < smallest_t || smallest_t == -1)
            {
                smallest_t = t;
                closest_object = o;
                closest_intersection = c + vect.getP() * t;
                closest_normal = o->normal(closest_intersection).normalize();
            }
        }
    }

    if (!closest_object)
        return color;

    Vector3 n = closest_normal.normalize();
    Vector3 vect_ = vect.normalize();
    Vector3 s = (vect_ - n * 2 * (n * vect_)).normalize();
    std::map<std::string, double> info = closest_object->getTextureInfo();
    Color object_color = closest_object->getColor();

    Color *tmp_ = new Color(0);

    for (auto light : scene_.getLights())
    {
        Vector3 l = Vector3(light->getPosition() - closest_intersection).normalize();

        bool shadow = false;
        double distance = l.getNorm();
        for (auto o : scene_.getObjects())
        {
            double t = -1;
            if (o != closest_object && o->intersect(closest_intersection, l, t) && t < smallest_t )
            {
                double distance2 = Vector3(Point3(closest_intersection + l.getP() * t) - closest_intersection).getNorm();

                if (distance < distance2)
                    continue;

                shadow = true;
                break;
            }
        }

        if (shadow)
            continue;

        double intensity = light->getIntensity();

        Plane *plane = dynamic_cast<Plane*>(closest_object);
        if (plane != nullptr && n * l < 0)
            n = n * -1;

        *tmp_ = *tmp_
            + object_color * info["kd"] * intensity * std::max(0.0, n * l)
            + object_color * info["ks"] * intensity * std::pow(std::max(0.0, s * l), info["ns"]);
    }

    // Color* reflection = castRay(closest_intersection, s, depth + 1);

    // *tmp_ = *tmp_ + *reflection * info["kr"];

    // delete reflection;
    delete color;
    color = tmp_;

    return color;
}
