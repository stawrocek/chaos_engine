#version 330 core
layout(triangles) in;
layout (line_strip, max_vertices = 2) out;
//layout(triangle_strip, max_vertices=3) out;

uniform mat4 mx;
uniform mat4 mxViewModel;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

out vec4 outColor;

void main()
{
	vec3 N = -GetNormal() * 0.2;
	//vec4 N = vec4(1.0, 0.0, 0.0, 1.0);
	// Center of the triangle
	vec3 P = ((gl_in[0].gl_Position+gl_in[1].gl_Position+gl_in[2].gl_Position) / 3.0).xyz;
	
	outColor=vec4(1.0, 0.0, 0.0, 1.0);
	gl_Position = mx * vec4(P, 1);
	EmitVertex();
	
	outColor=vec4(0.0, 0.0, 1.0, 1.0);
	gl_Position = mx *vec4((P + N * 5.0), 1.0);
	EmitVertex();
	EndPrimitive();
}