#ifndef __CONTROL_PANEL__
#define __CONTROL_PANEL__

#include "ImGuiRenderer.h"
#include "EventSystem/AbstractEvent.h"
#include <vector>

class ControlPanel: public ImGuiRenderer, public AbstractEvent{
    protected:
    std::vector<const char*> mSessionType;
    bool mPlay;
    float mReplayTime;

    void SetupWindow();

    public:
    ControlPanel();
    void event(std::string eventName,EventParam* param = nullptr);
};

#endif