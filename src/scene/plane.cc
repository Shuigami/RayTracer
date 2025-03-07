#include "scene/plane.hh"
#include "geometry/vector.hh"
#include "scene/object.hh"

Plane::Plane(Point3 p, Vector3 u, Vector3 v, UniformTexture* texture)
: Object(texture), p_(p), u_(u), v_(v)
{
}

bool Plane::intersect(const Point3& d, const Vector3& vect, double &t) const
{
    /*
    auto delta_x = d.getX() - p_.getX();
    auto delta_y = d.getY() - p_.getY();
    auto delta_z = d.getZ() - p_.getZ();

    std::cout << "delta_x: " << delta_x << std::endl;
    std::cout << "delta_y: " << delta_y << std::endl;
    std::cout << "delta_z: " << delta_z << std::endl;

    auto uy_ux = u_.getP().getY() / u_.getP().getX();
    auto uz_ux = u_.getP().getZ() / u_.getP().getX();

    std::cout << "uy_ux: " << uy_ux << std::endl;
    std::cout << "uz_ux: " << uz_ux << std::endl;

    auto vy_prime = v_.getP().getY() - v_.getP().getX() * uy_ux;
    auto vz_prime = v_.getP().getZ() - v_.getP().getX() * uz_ux;

    std::cout << "vy_prime: " << vy_prime << std::endl;
    std::cout << "vz_prime: " << vz_prime << std::endl;

    auto wy_prime = vect.getP().getY() - vect.getP().getX() * uy_ux;
    auto wz_prime = vect.getP().getZ() - vect.getP().getX() * uz_ux;

    std::cout << "wy_prime: " << wy_prime << std::endl;
    std::cout << "wz_prime: " << wz_prime << std::endl;

    auto delta_y_prime = delta_y - delta_x * uy_ux;
    auto delta_z_prime = delta_z - delta_x * uz_ux;

    std::cout << "delta_y_prime: " << delta_y_prime << std::endl;
    std::cout << "delta_z_prime: " << delta_z_prime << std::endl;

    auto denominator = (u_.getP().getX() * v_.getP().getY() - v_.getP().getX() * u_.getP().getY()) * vect.getP().getZ()
        + (v_.getP().getX() * u_.getP().getZ() - u_.getP().getX() * v_.getP().getZ()) * vect.getP().getY()
        + (u_.getP().getX() * v_.getP().getZ() - v_.getP().getX() * u_.getP().getZ()) * vect.getP().getX();

    std::cout << "denominator: " << denominator << std::endl;

    if (denominator <= 0.001)
        return false;

    auto nominator = (u_.getP().getX() * v_.getP().getY() - v_.getP().getX() * u_.getP().getY()) * delta_z
        + (v_.getP().getX() * u_.getP().getZ() - u_.getP().getX() * v_.getP().getZ()) * delta_y
        + (u_.getP().getX() * v_.getP().getZ() - v_.getP().getX() * u_.getP().getZ()) * delta_x;

    t = nominator / denominator;
    */

    Vector3 n = normal(d);
    double denominateur = n * vect;

    if (std::abs(denominateur) < 0.001)
        return false;

    Vector3 w = (p_ - d);
    t = (n * w) / denominateur;

    if (t < 0.001)
        return false;

    return true;
}

Vector3 Plane::normal(const Point3&) const
{
    return u_.cross(v_).normalize();
}

const Point3& Plane::getP() const
{
    return p_;
}

const Vector3& Plane::getU() const
{
    return u_;
}

const Vector3& Plane::getV() const
{
    return v_;
}
