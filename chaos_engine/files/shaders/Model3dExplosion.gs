#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform float time;

in VS_OUT{
	vec2 uvCoords;
	vec3 vNormal;
} gs_in[];

out vec2 uv;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main()
{
	//vec3 normal = (gs_in[0].vNormal + gs_in[1].vNormal + gs_in[2].vNormal)/3.0;
	vec3 normal = GetNormal()*3.0f;
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position+normal*((sin(time)+1.0)/2.0);
		uv=gs_in[i].uvCoords;
		EmitVertex();
	}
	EndPrimitive();
} 