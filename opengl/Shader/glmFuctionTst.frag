
#version 330 core 

in vec2 TexCoord ;
out vec4 Color;

uniform sampler2D texture0;

void main()
{
	Color = texture(texture0,TexCoord);
}