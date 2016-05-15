#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "gameobject.h"
#include "game.h"
#include "camera.h"

class Renderable {
public:
    virtual ~Renderable() {};

    virtual void setup() = 0;

    virtual void renderInstance(GameObject *obj, Game *game, Camera *camera) = 0;
};

#endif
