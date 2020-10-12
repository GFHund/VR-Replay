#ifndef __CONTROL_PANEL__
#define __CONTROL_PANEL__

#include "ImGuiRenderer.h"

class ControlPanel: public ImGuiRenderer{
    protected:
    void SetupWindow();
};

#endif