#version 330 core
in vec3 color;
in vec2 texPos;
uniform sampler2D tex;
out vec4 out_color;
void main()
{
    //out_color = vec4(color, 1.0);
    out_color = texture(tex,texPos);
}