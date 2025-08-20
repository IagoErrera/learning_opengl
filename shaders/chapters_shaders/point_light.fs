
#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess; 
};

struct DirectionalLight {
	vec3 direction;	
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
	vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
};


struct SpotLight {
	vec3 position;
	vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float cutOff;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord; 
  
uniform vec3 viewPos;
uniform Material material;
uniform PointLight light;  

out vec4 FragColor;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord)).rgb; 

	vec3 norm     = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff    = max(dot(norm, lightDir), 0.0);
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)).rgb;

	vec3 viewDir    = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular   = light.specular * (spec * vec3(texture(material.specular, TexCoord))).rgb;	
	
	float distance    = length(light.position - FragPos);
	float attenuation = 1.0f / (
		light.constant + 
		light.linear * distance +
		light.quadratic * distance * distance
	); 

	vec3 result = (ambient + diffuse + specular) * attenuation;
	
    FragColor   = vec4(result, 1.0);
}
