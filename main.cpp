#include <iostream>
#include <fstream>
#include <cmath>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "Light.h"

using namespace std;

double clamp(double value) {
    if (value < 0) return 0;
    if (value > 1) return 1;
    return value;
}

int main() {
    int width = 500;
    int height = 500;

    
    Scene scene;
    // SceneLoader::loadScene("scene/scene1.txt", scene);
    // SceneLoader::loadScene("scene/scene2.txt", scene);
    SceneLoader::loadScene("scene/scene3.txt", scene);
    // SceneLoader::loadScene("scene/scene4.txt", scene);
    // SceneLoader::loadScene("scene/scene5.txt", scene);

    Vec3 eye = scene.eye;

    Vec3 specularColor(1.5,1.5,1.5);

    // ofstream image("scene_output.ppm");
    // ofstream image("scene2_output.ppm");
    ofstream image("scene3_output.ppm");
    // ofstream image("scene4_output.ppm");
    // ofstream image("scene5_output.ppm");

    image << "P3\n";
    image << width << " " << height << "\n";
    image << "255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            double screenX = -1.0 + 2.0 * x / (width - 1);
            double screenY =  1.0 - 2.0 * y / (height - 1);

            Vec3 pixel(screenX, screenY, 0);
            Ray ray(eye, pixel - eye);

            Vec3 color(0, 0, 0);

            Sphere hitSphere;
            double sphereT;
            bool hasSphere =
                scene.findClosestSphere(ray, hitSphere, sphereT);

            Plane hitPlane;
            double planeT;
            bool hasPlane =
                scene.findClosestPlane(ray, hitPlane, planeT);

            bool sphereCloser =
                hasSphere && (!hasPlane || sphereT < planeT);

            if (sphereCloser) {
                Vec3 hitPoint = ray.pointAt(sphereT);
                Vec3 normal = hitSphere.getNormal(hitPoint);

                color = hitSphere.material.color * scene.ambient;

                for (const Light& light : scene.lights) {
                    double lightScale = 1.2;
                    double spotFactor = 1.0;

                    Vec3 L;
                    if (light.isSpot) {
                        L = (light.position - hitPoint).normalize();

                        Vec3 fromLightToPoint =
                            (hitPoint - light.position).normalize();

                        Vec3 spotDir =
                            light.direction.normalize();

                        double angle =
                            fromLightToPoint.dot(spotDir);

                        if (angle < light.cutoff) {
                            spotFactor = 0.1;
                        }
                    } 
                    else {
                        L = (light.direction * -1).normalize();
                    }
                    Vec3 shadowOrigin = hitPoint + normal * 0.001;
                    Ray shadowRay(shadowOrigin, L);

                    Sphere shadowSphere;
                    double shadowT;

                    bool inShadow =
                        scene.findClosestSphere(shadowRay, shadowSphere, shadowT);

                    double diffuse = normal.dot(L);
                    if (diffuse < 0) diffuse = 0;

                    Vec3 viewDir = (eye - hitPoint).normalize();

                    Vec3 reflectDir =
                        (normal * (2.0 * normal.dot(L)) - L).normalize();

                    double specular = viewDir.dot(reflectDir);
                    if (specular < 0) specular = 0;

                   if (inShadow) {
                        diffuse *= 0.3;
                        specular *= 0.2;
                    }

                    specular = pow(specular, hitSphere.material.shininess);

                    color =
                            color +
                            (hitSphere.material.color * diffuse) *
                            (light.intensity * lightScale * spotFactor) +

                            (specularColor * specular) *
                            (light.intensity * lightScale * spotFactor);
                }
            }

            else if (hasPlane) {
                Vec3 hitPoint = ray.pointAt(planeT);
                Vec3 normal = hitPlane.getNormal();

                Vec3 planeColor = hitPlane.material.color;

                bool isHorizontal =
                    fabs(hitPlane.normal.y) > 0.5;

                if (isHorizontal) {

                    int checkX = (int)floor(hitPoint.x * 3);
                    int checkZ = (int)floor(hitPoint.z * 3);

                    bool isDark =
                        (checkX + checkZ) % 2 == 0;

                    if (isDark) {
                        planeColor = planeColor * 0.7;
                    }
                    }
                    else {

                        planeColor = planeColor * 0.4;
                    }
                color = planeColor * scene.ambient;

                for (const Light& light : scene.lights) {
                    double lightScale = 1.2;
                    double spotFactor = 1.0;

                    Vec3 L;

                    if (light.isSpot) {
                        L = (light.position - hitPoint).normalize();

                        Vec3 fromLightToPoint =
                            (hitPoint - light.position).normalize();

                        Vec3 spotDir =
                            light.direction.normalize();

                        double angle =
                            fromLightToPoint.dot(spotDir);

                        if (angle < light.cutoff) {
                            spotFactor = 0.1;
                        }
                    } 
                    else {
                        L = (light.direction * -1).normalize();
                    }
                    
                    Vec3 shadowOrigin = hitPoint + normal * 0.001;
                    Ray shadowRay(shadowOrigin, L);

                    Sphere shadowSphere;
                    double shadowT;

                    bool inShadow =
                        scene.findClosestSphere(shadowRay, shadowSphere, shadowT);

                    double diffuse = normal.dot(L);
                    if (diffuse < 0) diffuse = 0;

                    if (light.isSpot) {
                        diffuse = 1.0;  // make spotlight visible on walls
                    }

                    if (inShadow) {
                        diffuse *= 0.3;
                    }

                    color =
                            color +
                            (planeColor * diffuse) *
                            (light.intensity * lightScale * spotFactor);
                }
            }
            int r = (int)(255 * clamp(color.x));
            int g = (int)(255 * clamp(color.y));
            int b = (int)(255 * clamp(color.z));

            image << r << " " << g << " " << b << " ";
        }

        image << "\n";
    }

    image.close();

    cout << "Created scene_output.ppm" << endl;
    return 0;
}