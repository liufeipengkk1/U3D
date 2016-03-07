#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 color ;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	//color = vec4(lightColor * objectColor, 1.0f);
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = diff * lightColor;
	
	vec3 result = (ambient + diffuse) * objectColor ;// mix
	color = vec4(result,1.0f);
}
