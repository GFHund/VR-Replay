#include "VrReplay.h"

#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "renderer/Renderer.h"
#include "objects/Rectangle.h"
#include "ControlPanel.h"

#include "Exceptions/InitFontException.h"
#include "Exceptions/LoadingFontException.h"
#include "Exceptions/SetFontSizeException.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


VrReplay::VrReplay(){}
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

    ControlPanel cp;
    cp.init(window);


    Renderer renderObj;
    int display_w = 640;
    int display_h = 480;
    renderObj.init(display_w,display_h);
    
    std::cout << "Start Loop" << std::endl;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(window))
    {
        //renderObj.render3DObject(&rect);
        //std::cout << "Im Gui Render Init" << std::endl;
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        cp.render(window,width,height);

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, display_w, display_h);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "End Loop" << std::endl;

    cp.shutdown(window);

    glfwDestroyWindow(window);

    glfwTerminate();
}
