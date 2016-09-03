#pragma once

#include "gameobject.h"
#include "game.h"
#include "camera.h"

class Renderable {
public:
    virtual ~Renderable() {};

    virtual void setup() = 0;

    virtual void renderInstance(GameObject *obj, Game *game, Camera *camera) = 0;
};
