#include "Ray.h"

Ray::Ray() {}

Ray::Ray(Vec3 origin, Vec3 direction) {
    this->origin = origin;
    this->direction = direction.normalize();
}

Vec3 Ray::pointAt(double t) const {
    return origin + direction * t;
}