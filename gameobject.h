#pragma once

#include <vector>

#include "behavior.h"
#include "scenegraph.h"

class GameObject {
public:
    SceneNode n; // this stores transform data :)
    std::vector<Behavior> behaviors; // stores "behaviors": basically the equivalent of Unity's MonoBehaviors.
    // It *should* eventually pull them in from a scripting language.

    void setPosition(float x, float y, float z);
};
