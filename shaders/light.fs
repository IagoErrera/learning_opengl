#version 330 core
#define N_DIRECTIONAL_LIGHTS 1
#define N_POINT_LIGHTS 4
#define N_SPOT_LIGHTS 1
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
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords; 
  
uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight directionalLights[N_DIRECTIONAL_LIGHTS];
uniform SpotLight spotLights[N_SPOT_LIGHTS];
uniform PointLight pointLights[N_POINT_LIGHTS];  

out vec4 FragColor;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = vec3(0.0f);
	for (int i = 0; i < N_DIRECTIONAL_LIGHTS; i++) 
		result += CalcDirectionalLight(directionalLights[i], norm, viewDir);	
	for (int i = 0; i < N_POINT_LIGHTS; i++) 
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	for (int i = 0; i < N_SPOT_LIGHTS; i++) 
		result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
	
	FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
 		
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {	
	vec3 lightDir = normalize(light.position - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (
		light.constant +
		light.linear * distance +
		light.quadratic * (distance * distance)
	);    
	
    vec3 ambient = attenuation * light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = attenuation * light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    vec3 specular = attenuation * light.specular * spec * texture(material.specular, TexCoords).rgb;  

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);
    
	float diff = max(dot(normal, lightDir), 0.0);
    
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
	float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (
		light.constant +
		light.linear * distance +
		light.quadratic * (distance * distance)
	);    
    
	float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
   
	ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
   
	return (ambient + diffuse + specular);
}
