#include "geometry/point.hh"
#include "geometry/vector.hh"
#include "motor/motor.hh"
#include "object/cube.hh"
#include "object/triangle.hh"
#include "scene/camera.hh"
#include "light/light.hh"
#include "object/object.hh"
#include "object/plane.hh"
#include "light/point_light.hh"
#include "scene/scene.hh"
#include "object/sphere.hh"
#include "texture/uniform_texture.hh"

#include <cmath>

int main()
{
    Camera camera(Point3(10, 0, 10), Point3(0, 0, 0), Vector3(Point3(0, 1, 0)), 46.5, 46.5, 2.8);

    PointLight* light = new PointLight(Color(255, 255, 255), Point3(0, 2, 3), 1);

    Plane* plane = new Plane(Point3(0, -1, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), UniformTexture::Plastic(Color(255)));
    Plane* plane2 = new Plane(Point3(0, 0, -1), Vector3(1, 0, 0), Vector3(0, 1, 0), UniformTexture::Metal(Color(255)));

    Triangle* triangle = new Triangle(Point3(0, 0, 0), Point3(0, 1, 0), Point3(1, 0, 0), UniformTexture::PlasticMat(Color(255, 0, 0)));
    Triangle* triangle2 = new Triangle(Point3(1, 0, 0), Point3(0, 1, 0), Point3(1, 1, 0), UniformTexture::PlasticMat(Color(0, 255, 0)));

    std::list<Object*> objects;
    objects.push_front(plane);
    objects.push_front(plane2);
    objects.push_front(triangle);
    objects.push_back(triangle2);

    std::list<Light*> lights;
    lights.push_front(light);

    Scene scene(objects, lights, camera);
    Motor motor(scene);

    Image image = motor.render();

    image.image_to_ppm("image.ppm");
}
