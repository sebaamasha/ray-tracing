#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

class Plane {
public:
    Material material;

    Vec3 normal;
    double d;

    Plane();

    Plane(Vec3 normal, double d, Material material);

    bool intersect(const Ray& ray, double& t) const;

    Vec3 getNormal() const;
};