#ifndef __ABSTRACT_STATE__
#define __ABSTRACT_STATE__
#include "../renderer/Renderer.h"
class AbstractState{
    public:
    virtual void init(Renderer renderer) = 0;
    virtual void tick() = 0;
    virtual void render(Renderer renderer) = 0;
    virtual void finish(Renderer renderer) = 0;
};

#endif