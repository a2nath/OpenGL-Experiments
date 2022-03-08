#include "DiffuseLight.h"

using namespace Rendering::Models;

DiffuseLight::DiffuseLight()
{
}

DiffuseLight::~DiffuseLight()
{
}
void DiffuseLight::Create()
{
	GLuint vbo;
	this->vbos.push_back(vbo);
}

void DiffuseLight::Update()
{
	offset = camera.GetPosition();
	//offset = Lighting.gDiffuse;
}

void DiffuseLight::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glUniform4fv(glGetUniformLocation(program, "ambientLight"), 1, &(Lighting.gAmbient)[0]);
	glUniform3fv(glGetUniformLocation(program, "lightPositionWorld"), 1, &offset[0]);
	glUniform1i(glGetUniformLocation(program, "flashon"), Lighting.flashon);
	glUniform3fv(glGetUniformLocation(program, "eyePositionWorld"), 1, &(camera.GetPosition())[0]);
}