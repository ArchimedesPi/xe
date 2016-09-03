#pragma once

#include <vector>
#include "scenegraph.h"
#include "gameobject.h"

class Scene {
public:
    Scene() : rootNode() {}

    void addObject(GameObject *object);

    std::vector<GameObject*> objects;
    SceneNode rootNode;
};
