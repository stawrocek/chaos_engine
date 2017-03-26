#version 330 core
out vec4 color;

in vec3 fragmentPosition;  
in vec3 normalVector;  

#define MAXIMUM_POINT_LIGHTS 8
#define MAXIMUM_DIRECTIONAL_LIGHTS 4

struct Material {
    vec4 diffuseColor;
    vec4 specularColor;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec4 color;
    float constant;
    float linear;
    float quadratic;
	float diffuseStrength;
	float specularStrength;
};

struct DirectionalLight{
	vec3 direction;
	vec4 color;
	float diffuseStrength;
	float specularStrength;
};

uniform vec4 ambientColor;
uniform float ambientStrength;

uniform Material uniMaterial;


uniform PointLight uniPointLight[MAXIMUM_POINT_LIGHTS];
uniform DirectionalLight uniDirLight[MAXIMUM_DIRECTIONAL_LIGHTS];

uniform vec3 uniViewPos;
uniform vec4 uniObjectColor;

uniform int uniPointLightsCount;
uniform int uniDirLightsCount;

vec3 calcPointLight(PointLight pointLight, vec3 norm, vec3 viewDir){	
    // Diffuse 
    vec3 lightDir = normalize(pointLight.position - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = pointLight.diffuseStrength * diff * pointLight.color;
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uniMaterial.shininess);
    vec4 specular = pointLight.specularStrength * spec * pointLight.color;  
    
	float distance = length(pointLight.position - fragmentPosition);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));  
	diffuse *= attenuation;
	specular *= attenuation;
	
    vec4 result = (diffuse + specular) * uniObjectColor;
    return result.xyz;
} 

vec3 calcDirLight(DirectionalLight dirLight, vec3 norm, vec3 viewDir){
	vec3 lightDir = normalize(-dirLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = dirLight.diffuseStrength * diff * dirLight.color;
	
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uniMaterial.shininess);
	vec4 specular = dirLight.specularStrength * spec * dirLight.color;  
	vec4 result = (diffuse + specular) * uniObjectColor;
    return result.xyz;
}

void main()
{
	vec3 norm = normalize(normalVector);
    vec3 viewDir = normalize(uniViewPos - fragmentPosition);
    vec3 result = vec4(ambientStrength * ambientColor).xyz;
	for(int i = 0; i < uniDirLightsCount; i++){
		result += calcDirLight(uniDirLight[i], norm, viewDir);
	}
	for(int i = 0; i < uniPointLightsCount; i++){
		result += calcPointLight(uniPointLight[i], norm, viewDir);
	}
	color = vec4(result.xyz, 1);
}