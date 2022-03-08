#version 400 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;

uniform mat4 VP;
uniform mat4 MV;
out vec2 texcoord;
void main()
{
	texcoord = in_texture;
	gl_Position = VP * MV * vec4(in_position, 1);
}