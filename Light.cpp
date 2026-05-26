#include "Light.h"

Light::Light() {
    direction = Vec3(0, 0, -1);
    position = Vec3(0, 0, 0);
    intensity = Vec3(1, 1, 1);
    isSpot = false;
    cutoff = 0;
}

Light::Light(Vec3 direction, Vec3 intensity) {
    this->direction = direction.normalize();
    this->intensity = intensity;
    this->position = Vec3(0, 0, 0);
    this->isSpot = false;
    this->cutoff = 0;
}

Light::Light(Vec3 direction, Vec3 position, Vec3 intensity, double cutoff) {
    this->direction = direction.normalize();
    this->position = position;
    this->intensity = intensity;
    this->isSpot = true;
    this->cutoff = cutoff;
}