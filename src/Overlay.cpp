#include "Overlay.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "renderer/Renderer.h"
#include "objects/Rectangle.h"

#include "Exceptions/InitFontException.h"
#include "Exceptions/LoadingFontException.h"
#include "Exceptions/SetFontSizeException.h"

#include "stateMachine/StateMachine.h"
#include "stateMachine/LastLapTimeState.h"


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Overlay::Overlay(){}
void Overlay::init(){
    GLFWwindow* window;
    int width, height;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        std::cout << "glfwInit failed"; 
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

    window = glfwCreateWindow(640, 480, "My Title",  NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        // Window or context creation failed
        std::cout << "window creation failed"<<'\n';
        return;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    StateMachine sm;
    LastLapTimeState* llts = new LastLapTimeState();
    sm.addState("LastLapTime",llts);
    sm.setStartState("LastLapTime");

    Renderer renderObj;
    renderObj.init(640,480);
    sm.init(renderObj);


    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);

        //renderObj.render3DObject(&rect);
        sm.loop(renderObj);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    sm.finish(renderObj);
}
/*
Rectangle rect = Rectangle();
    
    //rect.setImage(0,img);
    
    RenderFont font;
    try{
        font.init();
        font.setBgColor(0,0,0,100);
        Image* fontImg = font.renderFont("Hallo Welt, Oh du schöne Welt");
        rect.setImage(0,fontImg);
    }
    catch(InitFontException e){
        std::cout << e.what()<<std::endl;
        return;
    }
    catch(LoadingFontException e){
        std::cout << e.what() << std::endl;
        return;
    }
    catch(SetFontSizeException e){
        std::cout << e.what() << std::endl;
        return;
    }
    
    
    
    Shader* sha =  nullptr;
    try{
        //                               vertexProgram.glsl   fragmentProgram.glsl
        sha = Shader::getShaderPrograms("vertexProgram.glsl","fragmentProgram.glsl");
    }catch(ShaderReadFailureException e){
        std::cout << "Shader Read Failure Exception" << std::endl;
        return;
    }
    
    rect.setShader(sha);
    Renderer renderObj;
    renderObj.init(640,480);
    renderObj.init3DObject(&rect);

*/