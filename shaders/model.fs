#version 330 core

#define MAX_N_DIRECTIONAL_LIGHTS 1
#define MAX_N_POINT_LIGHTS 10
#define MAX_N_SPOT_LIGHTS 5

#define MAX_DIFFUSE_TEXTURES 5
#define MAX_SPECULAR_TEXTURES 5

struct Material {
	sampler2D diffuse[MAX_DIFFUSE_TEXTURES];
	int n_diffuse;
	sampler2D specular[MAX_SPECULAR_TEXTURES];
	int n_specular;
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

uniform DirectionalLight directionalLights[MAX_N_DIRECTIONAL_LIGHTS];
uniform int n_directional_lights = 0;

uniform SpotLight spotLights[MAX_N_SPOT_LIGHTS];
uniform int n_spot_lights = 0;

uniform PointLight pointLights[MAX_N_POINT_LIGHTS];  
uniform int n_point_lights = 0;

out vec4 FragColor;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = vec3(0.0f);
	for (int i = 0; i < n_directional_lights; i++) 
		result += CalcDirectionalLight(directionalLights[i], norm, viewDir);	
	for (int i = 0; i < n_point_lights; i++) 
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	for (int i = 0; i < n_spot_lights; i++) 
		result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
	
	if (n_directional_lights == 0 && n_point_lights == 0 && n_spot_lights == 0)
		result = texture(material.diffuse[0], TexCoords).rgb;
		
	FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * texture(material.diffuse[0], TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse[0], TexCoords).rgb;  
    vec3 specular = light.specular * spec * texture(material.specular[0], TexCoords).rgb;  
	
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
	
    vec3 ambient = attenuation * light.ambient * texture(material.diffuse[0], TexCoords).rgb;
    vec3 diffuse = attenuation * light.diffuse * diff * texture(material.diffuse[0], TexCoords).rgb;  
    vec3 specular = attenuation * light.specular * spec * texture(material.specular[0], TexCoords).rgb;  
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
    
	float theta     = dot(lightDir, normalize(-light.direction)); 
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient  = light.ambient * vec3(texture(material.diffuse[0], TexCoords));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse[0], TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular[0], TexCoords));
   
	ambient  *= attenuation * intensity;
    diffuse  *= attenuation * intensity;
    specular *= attenuation * intensity;
  
	return (ambient + diffuse + specular);
}
