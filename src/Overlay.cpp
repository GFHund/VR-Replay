#include "Overlay.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "Renderer.h"
#include "Rectangle.h"
#include "Exceptions/ShaderReadFailureException.h"
#include "Exceptions/InitFontException.h"
#include "Exceptions/LoadingFontException.h"
#include "Exceptions/SetFontSizeException.h"
#include "RenderFont.h"


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

    Rectangle rect = Rectangle();
    Image* img = new Image(512,512);
    for(int i=0; i< 512;i++){
        for(int k=0;k<512;k++){
            img->setPixel(i,k,200,200,200);
        }
        
    }
    //rect.setImage(0,img);
    
    RenderFont font;
    try{
        font.init();
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

    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);

        renderObj.render3DObject(&rect);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

  glfwTerminate();
}