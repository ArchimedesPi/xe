#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "gameobject.h"

class Renderable {
public:
    virtual ~Renderable() {};

    virtual void setup() = 0;
    virtual void renderInstance(GameObject *obj) = 0;
};

#endif
