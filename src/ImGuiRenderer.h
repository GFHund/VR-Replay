#ifndef __IMGUI_RENDERER__
#define __IMGUI_RENDERER__

#include "OpenGLHeaders.h"
#include "vendor/imgui/imgui.h"
#include "EventSystem/AbstractEvent.h"
#include <string>

class ImGuiRenderer:public AbstractEvent{
    private:
    // Data
    enum GlfwClientApi
    {
        GlfwClientApi_Unknown,
        GlfwClientApi_OpenGL,
        GlfwClientApi_Vulkan
    };
    unsigned int g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
    unsigned int g_VboHandle = 0, g_ElementsHandle = 0;
    GLFWcursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = {};
    bool g_MouseJustPressed[ImGuiMouseButton_COUNT] = {};
    GLint g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0; // Uniforms location
    GLuint g_AttribLocationVtxPos = 0, g_AttribLocationVtxUV = 0, g_AttribLocationVtxColor = 0; // Vertex attributes location
    GLuint g_FontTexture = 0;
    bool g_InstalledCallbacks = false;
    GLFWmousebuttonfun   g_PrevUserCallbackMousebutton = NULL;
    GLFWscrollfun        g_PrevUserCallbackScroll = NULL;
    GLFWkeyfun           g_PrevUserCallbackKey = NULL;
    GLFWcharfun          g_PrevUserCallbackChar = NULL;
    GlfwClientApi        g_ClientApi = GlfwClientApi_Unknown;
    double               g_Time = 0.0;

    protected:
    void imGuiInit(GLFWwindow* window);
    void imGuiRenderInit();
    void imGuiRender(ImDrawData* draw_data);
    void imGuiSetupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object);
    void imGuiShutdown(GLFWwindow* window);

    void UpdateMousePosAndButtons(GLFWwindow* window);
    void UpdateMouseCursor(GLFWwindow* window);
    void CreateFontsTexture();
    void NewFrame(GLFWwindow* window);
    bool CheckShader(GLuint handle, const char* desc);
    bool CheckProgram(GLuint handle, const char* desc);

    virtual void SetupWindow() = 0;

public:
    ImGuiRenderer();
    void init(GLFWwindow* window);
    void render(float deltaTime, GLFWwindow* window,int width,int height);
    void shutdown(GLFWwindow* window);
    void event(std::string eventName,EventParam* param = nullptr);
};

#endif 