#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <vector>
#include <string>
#include <map>
#include "AbstractState.h"
#include "../renderer/Renderer.h"

class StateMachine{
    private:
    std::map<std::string,AbstractState*> mStates;
    std::string mCurState;

    public:
    void init(Renderer renderer);
    void loop(Renderer renderer);
    void finish(Renderer renderer);

    void addState(std::string name, AbstractState* newState);
    void setStartState(std::string name);
};

#endif