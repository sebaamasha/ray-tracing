#pragma once

#include <vector>

#include "Sphere.h"
#include "Plane.h"
#include "Light.h"

class Scene {
public:
    
    std::vector<Sphere> spheres;

    std::vector<Plane> planes;
    std::vector<Light> lights;
    
    Vec3 eye;
    Vec3 ambient;

    void addSphere(const Sphere& sphere);

    void addPlane(const Plane& plane);

    bool findClosestSphere(
        const Ray& ray,
        Sphere& closestSphere,
        double& closestT
    ) const;

    bool findClosestPlane(
        const Ray& ray,
        Plane& closestPlane,
        double& closestT
    ) const;
};