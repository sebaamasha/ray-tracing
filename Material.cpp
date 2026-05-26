#include "Material.h"

Material::Material() {

    color = Vec3(1,1,1);

    shininess = 10;
}

Material::Material(
    Vec3 color,
    double shininess
) {

    this->color = color;

    this->shininess = shininess;
}