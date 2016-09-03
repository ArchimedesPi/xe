#pragma once

#include "scenegraph.h"

class GameObject {
public:
    SceneNode n; // this stores transform data :)

    void setPosition(float x, float y, float z);
};
