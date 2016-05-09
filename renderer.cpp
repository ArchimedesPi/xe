#include "renderer.h"

#include <vector>
#include <algorithm>
#include <functional>

void Renderer::addRenderable(Renderable *renderable) {
    this->renderables.push_back(renderable);
}

void Renderer::setupRenderables() {
    std::for_each(renderables.begin(), renderables.end(), std::mem_fn(&Renderable::setup));
}

void Renderer::renderInstances(std::vector<GameObject*> instances) {
}

void Renderer::renderInstance(GameObject *instance) {
    // how will we attach a renderer to an instance?
}

void Renderer::render(Renderable *renderable, GameObject *instance) {
    renderable->renderInstance(instance, game_);
}
