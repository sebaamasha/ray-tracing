#pragma once
#include "Vec3.h"

class Light {
public:
    Vec3 direction;
    Vec3 position;
    Vec3 intensity;

    bool isSpot;
    double cutoff;

    Light();

    Light(Vec3 direction, Vec3 intensity);

    Light(Vec3 direction, Vec3 position, Vec3 intensity, double cutoff);
};