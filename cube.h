#ifndef __TEST_CUBE_H__
#define __TEST_CUBE_H__

#include "gameobject.h"
#include "renderable.h"

class Cube : public GameObject {};

class CubeRenderer : public Renderable {
public:
    void render();

    virtual void render(GameObject *obj);
};

#endif
