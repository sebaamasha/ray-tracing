#pragma once

#include "Vec3.h"

class Material {
public:

    Vec3 color;

    double shininess;

    Material();

    Material(
        Vec3 color,
        double shininess
    );
};