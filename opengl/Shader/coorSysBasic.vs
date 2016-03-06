#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view ;
uniform mat4 projection;
uniform mat4 transform;

void main()
{
	gl_Position = projection * view * model * vec4(pos,1.0f);
	//gl_Position = transform * vec4(pos,1.0f);
	TexCoord = vec2(texCoord.x,1.0-texCoord.y);
}