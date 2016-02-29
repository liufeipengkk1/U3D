#version 330 core

in vec3 ourColor;

uniform float red ;
uniform float green ;
uniform float blue;

out vec4 color;

void main()
{
    color = vec4(ourColor.x * red,ourColor.y * green,ourColor.z * blue, 1.0f);
}