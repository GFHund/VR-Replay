#ifndef __REPLAY__
#define __REPLAY__

#include "../EventSystem/AbstractEvent.h"
#include "../renderer/Renderer.h"
#include "../objects/Cube.h"


class Replay: public AbstractEvent{
    private:
    float mReplayTime;
    Cube* cars[22];
    Cube* test;
    bool mPlay;
    float mMaxReplayTime;
    
    public:
    Replay();
    void init(Renderer renderer);
    void render(float deltaTime, Renderer renderer);
    void finish(Renderer renderer);
    void event(std::string eventName,EventParam* param = nullptr);

};

#endif