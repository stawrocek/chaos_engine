#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform float time;

in VS_OUT{
	vec2 uvCoords;
	vec3 vNormal;
} gs_in[];

out vec2 uv;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec3 normal = (gs_in[0].vNormal + gs_in[1].vNormal + gs_in[2].vNormal)/3.0;
	//for(int i=0; i<3; i++)
	//{
	//	//gl_Position = gl_in[i].gl_Position+vec4(rand(vec2(time, time*100.0)), rand(vec2(time, time*13.37)), rand(vec2(time*313.37)), 1.0);
	//	gl_Position = gl_in[i].gl_Position+vec4(0.0, rand(vec2(time, time*13.37)), 0.0, 1.0);
	//	uv=gs_in[i].uvCoords;
	//	EmitVertex();
	//}
	//EndPrimitive();
	
	gl_Position = gl_in[0].gl_Position;
	uv = gs_in[0].uvCoords;
	EmitVertex();
	
	gl_Position = gl_in[1].gl_Position+vec4(0.0, 1.0, 1.0, 1.0);
	uv = gs_in[1].uvCoords;
	EmitVertex();
	
	gl_Position = gl_in[2].gl_Position + vec4(0.0, rand(vec2(time, time*13.37)), 1.0, 1.0);
	uv = gs_in[2].uvCoords;
	EmitVertex();
} 