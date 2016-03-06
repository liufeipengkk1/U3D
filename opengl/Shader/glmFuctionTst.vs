
#version 330 core 

layout (location = 0) in vec3 pos ;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord ;

uniform mat4 transform; // for basic transformation
//uniform mat4 model;
//uniform mat4 view ;
uniform mat4 projection;


void main()
{
	//gl_Position = transform * vec4(pos,1.0f);
	//gl_Position = projection * view * model * vec4(pos,1.0f);
	gl_Position = projection * transform *vec4(pos,1.0f);
	//gl_Position = vec4(pos,1.0f);
	TexCoord = vec2(texCoord.x,1.0f - texCoord.y);

}