#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "renderable.h"
#include "gameobject.h"
#include "game.h"
#include "camera.h"

class Renderer {
public:
    Renderer(Game *game, Camera *camera) : game_(game), camera_(camera) {}

    void addRenderable(Renderable *renderable);
    void setupRenderables();

    void renderInstances(std::vector<GameObject*> instances);
    void renderInstance(GameObject *instance);
    void render(Renderable *renderable, GameObject *instance);

    std::vector<Renderable*> renderables;
    Camera *camera;

private:
    Game *game_;
    Camera *camera_;
};

#endif
