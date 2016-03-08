#version 330 core 

in vec3 FragPos ;
in vec3 Normal ;
in vec2 TexCoord;

out vec4 color;

// can add a lot of attributes.such as emission ..
//light maps
struct Material{
    sampler2D diffuse;  // using a map
    sampler2D specular; // using a map
    float     shininess;   
};

// we using attenuation
// the formula is att = 1/(kc + kl * d + kq *d*d)
//according to the range we choose th kl kq from table,
//http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
//kc = 1

struct Light{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord));
    
    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoord));
    
    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
    
    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation ;
    color = vec4(ambient+diffuse + specular,1.0f);
    
}