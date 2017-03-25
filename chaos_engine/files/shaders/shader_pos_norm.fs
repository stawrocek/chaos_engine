#version 330 core
out vec4 color;

in vec3 fragmentPosition;  
in vec3 normalVector;  

#define MAXIMUM_POINT_LIGHTS 8

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
};

uniform vec4 ambientColor;
uniform float ambientStrength;

uniform Material uniMaterial;


uniform PointLight uniPointLight[MAXIMUM_POINT_LIGHTS];
uniform vec3 uniViewPos;
uniform vec4 uniObjectColor;

uniform int uniLightsCount;

vec3 calcPointLight(PointLight pointLight){
	vec4 lightColor = pointLight.color;
	vec3 lightPos = pointLight.position;
	
	// Ambient
    vec4 ambient = ambientStrength * ambientColor;
  	
    // Diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(lightPos - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uniViewPos - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uniMaterial.shininess);
    vec4 specular = specularStrength * spec * lightColor;  
    
	float distance = length(pointLight.position - fragmentPosition);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));  
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
    vec4 result = (ambient + diffuse + specular) * uniObjectColor;
    return result.xyz;
} 

void main()
{
    vec3 result = vec3(0,0,0);
	for(int i = 0; i < uniLightsCount; i++){
		result += calcPointLight(uniPointLight[i]);
	}
	color = vec4(result.xyz, 1);
}