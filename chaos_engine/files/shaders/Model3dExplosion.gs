#version 330 compatibility
layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

uniform float time;

in VS_OUT{
	vec2 uvCoords;
} gs_in[];

out vec2 uv;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0f;
    vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude; 
    return position + vec4(direction, 0.0f);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main()
{
	vec3 normal = GetNormal();
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position+normal*((sin(time)+1.0)/2.0);
		uv=gs_in[i].uvCoords;
		EmitVertex();
	}
	EndPrimitive();
} 