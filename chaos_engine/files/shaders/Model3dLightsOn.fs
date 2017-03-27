#version 330 core
out vec4 color;

in vec3 fragmentPosition;  
in vec3 normalVector;  
in vec2 uvCoords;

#define MAXIMUM_POINT_LIGHTS 8
#define MAXIMUM_DIRECTIONAL_LIGHTS 4
#define MAXIMUM_SPOTLIGHT_LIGHTS 8

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

struct Spotlight {
    vec3 position;
	vec3 direction;
    vec4 color;
	float cutoffCosine;
    float constant;
    float linear;
    float quadratic;
	float diffuseStrength;
	float specularStrength;
};

uniform sampler2D tex0;
uniform vec4 uniColor;

uniform vec4 ambientColor;
uniform float ambientStrength;

uniform Material uniMaterial;

uniform PointLight uniPointLight[MAXIMUM_POINT_LIGHTS];
uniform DirectionalLight uniDirLight[MAXIMUM_DIRECTIONAL_LIGHTS];
uniform Spotlight uniSpotlight[MAXIMUM_SPOTLIGHT_LIGHTS];

uniform vec3 uniViewPos;
uniform vec4 uniObjectColor;

uniform int uniPointLightsCount;
uniform int uniDirLightsCount;
uniform int uniSpotlightsCount;

vec3 calcPointLight(PointLight pointLight, vec3 norm, vec3 viewDir){	
    // Diffuse 
    vec3 lightDir = normalize(pointLight.position - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = pointLight.diffuseStrength * diff * pointLight.color * texture(tex0, uvCoords);
    
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
	vec4 diffuse = dirLight.diffuseStrength * diff * dirLight.color * texture(tex0, uvCoords);
	
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uniMaterial.shininess);
	vec4 specular = dirLight.specularStrength * spec * dirLight.color;  
	vec4 result = (diffuse + specular) * uniObjectColor;
    return result.xyz;
}

vec3 calcSpotlight(Spotlight spotlight, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(-spotlight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = spotlight.diffuseStrength * diff * spotlight.color * texture(tex0, uvCoords);
    
	float thetaCosine = dot(lightDir, normalize(-spotlight.direction));
	if(thetaCosine < spotlight.cutoffCosine){
		return vec3(0,0,0);
	}
	
    float spec = pow(max(dot(viewDir, -spotlight.direction), 0.0), uniMaterial.shininess);
    vec4 specular = spotlight.specularStrength * spec * spotlight.color;  
	float distance = length(spotlight.position - fragmentPosition);
	float attenuation = 1.0 / (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * (distance * distance));  
	diffuse *= attenuation;
	specular *= attenuation;
	
    vec4 result = (diffuse + specular) * uniObjectColor;
    return result.xyz;
} 

void main()
{
	//color=vec4(0,1,0,1);
	vec3 norm = normalize(normalVector);
    vec3 viewDir = normalize(uniViewPos - fragmentPosition);
    vec3 result = vec4(ambientStrength * ambientColor).xyz;
	for(int i = 0; i < uniPointLightsCount; i++){
		result += calcPointLight(uniPointLight[i], norm, viewDir);
	}
	for(int i = 0; i < uniDirLightsCount; i++){
		result += calcDirLight(uniDirLight[i], norm, viewDir);
	}
	for(int i = 0; i < uniSpotlightsCount; i++){
		result += calcSpotlight(uniSpotlight[i], norm, viewDir);
	}
	color = vec4(result.xyz, 1);
	
}