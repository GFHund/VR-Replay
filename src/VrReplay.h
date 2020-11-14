#ifndef __F1_REPLAY__
#define __F1_REPLAY__
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "OpenGLHeaders.h"
#include "vendor/imgui/imgui.h"
#include "objects/Cube.h"
#include <chrono>

class VrReplay{
    private:
        std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<int,std::milli> > tp1,tp2;
        void registerEvents();
    public:
    VrReplay();
    void init();

    
};

#endif