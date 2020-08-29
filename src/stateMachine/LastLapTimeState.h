#ifndef __LAST_LAP_TIME_STATE__
#define __LAST_LAP_TIME_STATE__

#include "AbstractState.h"
#include "../objects/Ring.h"

class LastLapTimeState: public AbstractState{
    protected:
    Ring* ticker;
    
    public:
    void init(Renderer renderer);
    void tick();
    void render(Renderer renderer);
    void finish(Renderer renderer);
}; 

#endif