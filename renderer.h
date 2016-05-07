#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include "renderable.h"

class Renderer {
public:
    void renderAll();
    void render(Renderable *renderable);

    std::vector<Renderable*> renderables;
};

#endif
