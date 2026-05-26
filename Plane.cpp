#include "Plane.h"
#include <cmath>

Plane::Plane() {}

Plane::Plane(Vec3 normal, double d, Material material) {
    this->normal = normal.normalize();
    this->d = d;
    this->material = material;
}

bool Plane::intersect(const Ray& ray, double& t) const {

    double denom = normal.dot(ray.direction);

    if (fabs(denom) < 1e-6)
        return false;

    t = -(normal.dot(ray.origin) + d) / denom;

    return t >= 0;
}

Vec3 Plane::getNormal() const {

    return normal;
}