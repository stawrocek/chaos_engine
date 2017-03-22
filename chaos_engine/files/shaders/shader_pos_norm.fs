#version 330 core
out vec4 color;

in vec3 fragmentPosition;  
in vec3 normalVector;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec4 lightColor;
uniform vec4 objectColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(normalVector);
    vec3 lightDir = normalize(lightPos - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * lightColor;  
        
    vec4 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result.xyz, 1.0);
    //color = result;
} 