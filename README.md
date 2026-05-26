# Ray Tracing Project

## Description

This project implements a basic ray tracing renderer in C++.

The renderer supports:
- Spheres
- Planes
- Ambient lighting
- Directional lights
- Spot lights
- Diffuse shading
- Specular shading 
- Shadows
- Checkerboard floor pattern
- Multiple scenes loaded from text files

The program renders the scene into a `.ppm` image file.

---

# Project Structure

## Main Files

- `main.cpp` – rendering loop and ray tracing logic
- `Vec3.cpp / Vec3.h` – vector math operations
- `Ray.cpp / Ray.h` – ray representation
- `Sphere.cpp / Sphere.h` – sphere intersection and normals
- `Plane.cpp / Plane.h` – plane intersection and normals
- `Scene.cpp / Scene.h` – scene management
- `SceneLoader.cpp / SceneLoader.h` – loading scenes from text files
- `Material.cpp / Material.h` – material properties
- `Light.cpp / Light.h` – light representation

---

# Compile

Compile the project using:

cl main.cpp Vec3.cpp Ray.cpp Sphere.cpp Plane.cpp Scene.cpp SceneLoader.cpp Material.cpp Light.cpp
Run: ./main.exe

---
# Changing Scenes

scenes are loaded from the scene folder.

To change the rendered scene, edit:

    SceneLoader::loadScene("scene/scene1.txt", scene);

    and replace the scene file name with:

        * scene1.txt
        * scene2.txt
        * scene3.txt
        * scene4.txt
        * scene5.txt