#version 330 core
uniform mat4 MVP;
//layout(location = 0) in vec3 vCol;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;
//out vec3 color;
out vec2 texPos;
void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    //gl_Position = MVP * vec4(vTex, 0.0, 1.0);
    //color = vCol;
    texPos = vTex;
}