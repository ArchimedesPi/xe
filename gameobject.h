#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "scenegraph.h"

class GameObject {
public:
    SceneNode n; // this stores transform data :)

    void setPosition(float x, float y, float z);
};

#endif
