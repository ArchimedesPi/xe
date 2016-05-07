#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "gameobject.h"

class Renderable {
public:
    virtual ~Renderable();

    virtual void shaderSetup();
    virtual void render(GameObject *obj);
};

#endif
