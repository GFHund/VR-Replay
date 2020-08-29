#include "StateMachine.h"

void StateMachine::init(Renderer renderer){
    AbstractState* state = this->mStates.at(this->mCurState);
    state->init(renderer);
}
void StateMachine::loop(Renderer renderer){
    AbstractState* state = this->mStates.at(this->mCurState);
    state->tick();
    state->render(renderer);
}
void StateMachine::finish(Renderer renderer){
    
}

void StateMachine::addState(std::string name, AbstractState* newState){
    mStates.insert(std::pair<std::string,AbstractState*>(name,newState));
}

void StateMachine::setStartState(std::string name){
    mCurState = name;
}
