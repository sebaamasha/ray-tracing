#include "Sphere.h"
#include <cmath>

Sphere::Sphere() {}

Sphere::Sphere(
    Vec3 center,
    double radius,
    Material material
) {

    this->center = center;

    this->radius = radius;

    this->material = material;
}

bool Sphere::intersect(const Ray& ray, double& t) const {

    Vec3 oc = ray.origin - center;

    double a = ray.direction.dot(ray.direction);

    double b = 2.0 * oc.dot(ray.direction);

    double c = oc.dot(oc) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    t = (-b - sqrt(discriminant)) / (2.0 * a);

    return true;
}

Vec3 Sphere::getNormal(const Vec3& point) const {
    return (point - center).normalize();
}