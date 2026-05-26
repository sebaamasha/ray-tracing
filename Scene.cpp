#include "Scene.h"

#include <limits>

void Scene::addSphere(const Sphere& sphere) {

    spheres.push_back(sphere);
}

void Scene::addPlane(const Plane& plane) {

    planes.push_back(plane);
}

bool Scene::findClosestSphere(
    const Ray& ray,
    Sphere& closestSphere,
    double& closestT
) const {

    bool hit = false;

    closestT = std::numeric_limits<double>::infinity();

    for (const Sphere& sphere : spheres) {

        double t;

        if (sphere.intersect(ray, t)) {

            if (t > 0.001 && t < closestT) {

                closestT = t;

                closestSphere = sphere;

                hit = true;
            }
        }
    }

    return hit;
}

bool Scene::findClosestPlane(
    const Ray& ray,
    Plane& closestPlane,
    double& closestT
) const {

    bool hit = false;

    closestT = std::numeric_limits<double>::infinity();

    for (const Plane& plane : planes) {

        double t;

        if (plane.intersect(ray, t)) {

            if (t > 0.001 && t < closestT) {

                closestT = t;

                closestPlane = plane;

                hit = true;
            }
        }
    }

    return hit;
}