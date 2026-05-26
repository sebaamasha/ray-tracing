#pragma once

#include <string>
#include "Scene.h"

class SceneLoader {
public:

    static void loadScene(
        const std::string& filename,
        Scene& scene
    );
};