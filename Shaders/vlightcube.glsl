#version 400 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 normalModel;


out mat4 MV_out;
out vec3 surface_normal;


uniform mat4 VP;
uniform mat4 MV;
out vec4 color;
out vec3 vertexPositionWorld;

void main()
{
	surface_normal = normalModel;
	MV_out = MV;
	color = in_color;
	gl_Position = VP * MV * vec4(in_position, 1);
	vertexPositionWorld = vec3(MV * vec4(in_position,1.0));
}