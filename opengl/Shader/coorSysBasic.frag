
#version 330 core

in vec2 TexCoord;


uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

out vec4 color;

void main()
{
	color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
}
