#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "renderable.h"
#include "gameobject.h"
#include "game.h"

class Renderer {
public:
    Renderer(Game *game) : game_(game) {}

    void addRenderable(Renderable *renderable);
    void setupRenderables();

    void renderInstances(std::vector<GameObject*> instances);
    void renderInstance(GameObject *instance);
    void render(Renderable *renderable, GameObject *instance);

    std::vector<Renderable*> renderables;

private:
    Game *game_;
};

#endif
