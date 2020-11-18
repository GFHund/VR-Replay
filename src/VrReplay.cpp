#include "VrReplay.h"

#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "renderer/Renderer.h"
#include "Replay/Replay.h"
#include "objects/Rectangle.h"
#include "ControlPanel.h"
#include "Data/DataLayer.h"
#include "EventSystem/EventManager.h"

#include "Exceptions/InitFontException.h"
#include "Exceptions/LoadingFontException.h"
#include "Exceptions/SetFontSizeException.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


VrReplay::VrReplay(){}

static void MouseButtonCallback(GLFWwindow* window, int button,int action,int mods){
  EventParam* param = new EventParam();
  param->setInt("button",button);
  param->setInt("action",action);
  param->setInt("mods",mods);
  EventManager::getInstance()->fireEvent("MouseButtonCallback",param);
}
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
  EventParam* param = new EventParam();
  param->setInt("key",key);
  param->setInt("scancode",scancode);
  param->setInt("action",action);
  param->setInt("mods",mods);
  EventManager::getInstance()->fireEvent("KeyCallback",param);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void ScrollCallback(GLFWwindow* window, double xoffset,double yoffset){
  EventParam* param = new EventParam();
  param->setDouble("xoffset",xoffset);
  param->setDouble("yoffset",yoffset);
  EventManager::getInstance()->fireEvent("ScrollCallback",param);
}
static void CharCallback(GLFWwindow*, unsigned int c){
  EventParam* param = new EventParam();
  param->setInt("c",c);
  EventManager::getInstance()->fireEvent("CharCallback",param);
}

void VrReplay::registerEvents(GLFWwindow* window){
  glfwSetMouseButtonCallback(window, MouseButtonCallback);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetScrollCallback(window, ScrollCallback);
  glfwSetCharCallback(window, CharCallback);
}

void VrReplay::init(){
    GLFWwindow* window;
    int width = 640, height = 480;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        std::cout << "glfwInit failed"; 
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

    window = glfwCreateWindow(width, height, "My Title",  NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        // Window or context creation failed
        std::cout << "window creation failed"<<'\n';
        return;
    }
    
    glfwMakeContextCurrent(window);

    DataLayer::getInstance()->init();
    
    registerEvents(window);

    ControlPanel cp;
    cp.init(window);

    Renderer renderObj;
    int display_w = 640;
    int display_h = 480;
    renderObj.init(display_w,display_h);

    Replay replay;
    replay.init(renderObj);
    
    std::cout << "Start Loop" << std::endl;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    typedef std::chrono::duration<int,std::milli> milliSec;
    bool bFirst = true;
    while (!glfwWindowShouldClose(window))
    {
        //renderObj.render3DObject(&rect);
        //std::cout << "Im Gui Render Init" << std::endl;
        
        float deltaTime = 0.0f;
        if(bFirst){
            bFirst = false;
        }
        else{
            std::chrono::duration<int,std::milli> duration;
            duration = tp2-tp1;
            deltaTime = duration.count();
        }
        this->tp2 =  std::chrono::time_point_cast<milliSec>(std::chrono::system_clock::now());
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        replay.render(deltaTime, renderObj);
        cp.render(deltaTime,window,width,height);
        

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, display_w, display_h);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        this->tp1 =  std::chrono::time_point_cast<milliSec>(std::chrono::system_clock::now());
    }
    std::cout << "End Loop" << std::endl;

    cp.shutdown(window);
    replay.finish(renderObj);

    glfwDestroyWindow(window);

    glfwTerminate();
}
