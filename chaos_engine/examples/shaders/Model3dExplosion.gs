#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform float time;

in VS_OUT{
	vec2 uvCoords;
	vec3 vNormal;
} gs_in[];

out vec2 uv;

void main()
{
	vec3 normal = (gs_in[0].vNormal + gs_in[1].vNormal + gs_in[2].vNormal)/3.0;
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position+vec4(normal*((sin(time)+1.0)/2.0), 1.0);
		uv=gs_in[i].uvCoords;
		EmitVertex();
	}
	EndPrimitive();
} 