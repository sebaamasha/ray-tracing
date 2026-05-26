#pragma once
#include "Vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray();
    Ray(Vec3 origin, Vec3 direction);

    Vec3 pointAt(double t) const;
};