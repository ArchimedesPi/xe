#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "renderable.h"
#include "gameobject.h"

class Renderer {
public:
    void addRenderable(Renderable *renderable);
    void setupRenderables();

    void renderInstances(std::vector<GameObject*> instances);
    void renderInstance(GameObject *instance);
    void render(Renderable *renderable, GameObject *instance);

    std::vector<Renderable*> renderables;
};

#endif
