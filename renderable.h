#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "gameobject.h"
#include "game.h"

class Renderable {
public:
    virtual ~Renderable() {};

    virtual void setup() = 0;

    virtual void renderInstance(GameObject *obj, Game *game) = 0;
};

#endif
