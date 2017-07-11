#version 330 core
out vec4 color;

in vec3 textureDir; 
uniform samplerCube cubemap;

void main()
{             
    color = textureCube(cubemap, textureDir);
}  