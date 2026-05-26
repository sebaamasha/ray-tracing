#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

class Sphere {
public:

    Vec3 center;

    double radius;

    Material material;

    Sphere();

    Sphere(
        Vec3 center,
        double radius,
        Material material
    );

    bool intersect(
        const Ray& ray,
        double& t
    ) const;

    Vec3 getNormal(
        const Vec3& point
    ) const;
};