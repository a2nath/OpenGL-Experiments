#version 400 core
layout(location = 0) out vec4 out_color;

in vec4 color;
in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec4 ambientLight;
uniform vec3 eyePositionWorld;
uniform int flashon;
//uniform int specularExponent;

void main(void){

	float distance = length(lightPositionWorld - vertexPositionWorld);
	distance = distance * distance;

	//Diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);
	diffuseLight = flashon*clamp(diffuseLight, 0, 1)/distance;

	//Specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float cosAlpha = clamp( dot( eyeVectorWorld,reflectedLightVectorWorld ), 0,1 );
	float s = pow(cosAlpha,50);
	vec4 specularLight = vec4(s, s, s, 1)/distance;

	out_color =  vec4(color.xyz*(diffuseLight.xyz + ambientLight.xyz + specularLight.xyz), color.a);
}
