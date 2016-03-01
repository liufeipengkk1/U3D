
#version 330 core

in vec3 ourColor;
in vec2 TexCood ;

out vec4 color ;
uniform sampler2D outTexture;

void main()
{
	color = texture(outTexture,TexCood);
}