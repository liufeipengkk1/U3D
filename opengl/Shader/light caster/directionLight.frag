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

//direction light
struct Light{
    //vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoord));
    
    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
    
    color = vec4(ambient+diffuse + specular,1.0f);
    
}