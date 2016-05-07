#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <list>
#include "renderable.h"

class Renderer {
public:
    void renderAll();
    void render(Renderable *renderable);

    std::list<Renderable*> renderables;
};

#endif
