#version 400 core
layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;
in vec2 texcoord;

void main()
{
	
	float d = 1.0/256.0;
	vec4 left =   texture2D(texture1, texcoord - vec2(d, 0));
	vec4 right =  texture2D(texture1, texcoord + vec2(d, 0));
	vec4 bottom = texture2D(texture1, texcoord - vec2(0, d));
	vec4 top =    texture2D(texture1, texcoord + vec2(0, d));
	
	vec4 color = 100.0 * (abs(right - left) + abs(top - bottom));
	if(color.r >= .5 || color.g >= .5 || color.b >= .5)
		color = vec4(1,1,1,0);
	else
		color = vec4(0,0,0,0);

	out_color =  color;
	out_color.a = 1.0f;
}