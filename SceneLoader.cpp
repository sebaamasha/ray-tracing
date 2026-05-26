#include "SceneLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Material.h"
#include "Light.h"

void SceneLoader::loadScene(const std::string& filename, Scene& scene) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open scene file\n";
        return;
    }

    std::vector<Sphere> tempSpheres;
    std::vector<Plane> tempPlanes;
    std::vector<bool> isSphereOrder;
    std::vector<Vec3> lightDirections;
    std::vector<double> lightTypes;

    std::vector<Vec3> spotPositions;
    std::vector<double> spotCutoffs;

    std::vector<Vec3> lightIntensities;
    std::string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'e') {

            double x, y, z, w;

            ss >> x >> y >> z >> w;

            scene.eye = Vec3(x, y, z);
        }else if (type == 'a') {
            double r, g, b, w;
            ss >> r >> g >> b >> w;

            scene.ambient = Vec3(r, g, b);
        }

        if (type == 'o') {
            double a, b, c, d;
            ss >> a >> b >> c >> d;

            if (d > 0) {
                tempSpheres.push_back(
                    Sphere(Vec3(a, b, c), d, Material())
                );
                isSphereOrder.push_back(true);
            } else {
                tempPlanes.push_back(
                    Plane(Vec3(a, b, c), d, Material())
                );
                isSphereOrder.push_back(false);
            }
        }

        else if (type == 'c') {
            double r, g, b, shininess;
            ss >> r >> g >> b >> shininess;

            Material mat(Vec3(r, g, b), shininess);

            int colorIndex = scene.spheres.size() + scene.planes.size();

            if (colorIndex < isSphereOrder.size()) {
                if (isSphereOrder[colorIndex]) {
                    int sphereIndex = scene.spheres.size();
                    tempSpheres[sphereIndex].material = mat;
                    scene.addSphere(tempSpheres[sphereIndex]);
                } else {
                    int planeIndex = scene.planes.size();
                    tempPlanes[planeIndex].material = mat;
                    scene.addPlane(tempPlanes[planeIndex]);
                }
            }
        }
        else if (type == 'd') {
            double x, y, z, w;
            ss >> x >> y >> z >> w;

            lightDirections.push_back(Vec3(x, y, z));
            lightTypes.push_back(w);
        }

        else if (type == 'p') {
            double x, y, z, cutoff;
            ss >> x >> y >> z >> cutoff;

            spotPositions.push_back(Vec3(x, y, z));
            spotCutoffs.push_back(cutoff);
        }

        else if (type == 'i') {
            double r, g, b, w;
            ss >> r >> g >> b >> w;

            lightIntensities.push_back(Vec3(r, g, b));
        }
    }
    int spotIndex = 0;

    for (int i = 0; i < lightDirections.size(); i++) {
        if (lightTypes[i] == 0.0) {
            scene.lights.push_back(
                Light(lightDirections[i], lightIntensities[i])
            );
        }
        else {
            scene.lights.push_back(
                Light(
                    lightDirections[i],
                    spotPositions[spotIndex],
                    lightIntensities[i],
                    spotCutoffs[spotIndex]
                )
            );

            spotIndex++;
        }
    }
    file.close();
}