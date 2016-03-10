#version 330 core

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//define pointLight
#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color; 

uniform vec3 viewPos;
uniform DirLight dirLight; // direction light
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform Material material;

void CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
void CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight,norm,viewDir);
    
    for(int i = 0 ;i < NR_POINT_LIGHTS;i++)
    {
        result += CalcPointLight(pointLight[i] ,norm,FragPos,viewDir);
    }
    
    color = vec4(result,1.0f);
}

// light = posFrag - lightPos
vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
    //ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    
    //diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir,normal),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    
    //specular
    vec3 reflectDir = reflect(-lightDir,normal);
    vec3 spec = pow(max(dot(reflectDir,viewDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));
    
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    
    vec3 lightDir = normalize(light.position - fragPos);
    //diffuse
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
    //specular
    vec3 reflectDir = reflect(-lightDir,normal);
    vec3 spec = pow(max(dot(reflectDir,viewDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));
    
    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    
    ambient *= attenuation;
    specular *= attenuation;
    diffuse *= attenuation;
    
    return (ambient + diffuse + specular);
    
}