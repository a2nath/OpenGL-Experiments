#include "CubeTextured.h"

using namespace Rendering::Models;
using namespace Rendering;
float margin = .7f;
float fDeltaTime = 1 * camera.deltaTicks / (float)CLOCKS_PER_SEC;
CubeTextured::CubeTextured()
{
}

CubeTextured::~CubeTextured()
{
}


/* Inputs: Orientation | Offset | Scaling */
void CubeTextured::Create(glm::vec3& orientation, glm::vec3& offset, glm::vec3& scale)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int>  indices = {
		0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11 ,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23 }; //bottom
   //front
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, +1.0), glm::vec2(0, 0), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, +1.0), glm::vec2(1, 0), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, +1.0), glm::vec2(1, 1), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, +1.0), glm::vec2(0, 1), glm::vec3(0.0f, 0.0f, 1.0f)));

	//right
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, +1.0), glm::vec2(0, 0), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, -1.0), glm::vec2(1, 0), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, -1.0), glm::vec2(1, 1), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, +1.0), glm::vec2(0, 1), glm::vec3(1.0f, 0.0f, 0.0f)));

	//back
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, -1.0), glm::vec2(0, 0), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, -1.0), glm::vec2(1, 0), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, -1.0), glm::vec2(1, 1), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 1), glm::vec3(0.0f, 0.0f, -1.0f)));

	//left
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, +1.0), glm::vec2(1, 0), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, +1.0), glm::vec2(1, 1), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, -1.0), glm::vec2(0, 1), glm::vec3(-1.0f, 0.0f, 0.0f)));

	//upper
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, -1.0), glm::vec2(0, 0), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, -1.0), glm::vec2(1, 0), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, +1.0, +1.0), glm::vec2(1, 1), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, +1.0, +1.0), glm::vec2(0, 1), glm::vec3(0.0f, 1.0f, 0.0f)));

	////bottom
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, -1.0), glm::vec2(1, 0), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0, -1.0, +1.0), glm::vec2(1, 1), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, +1.0), glm::vec2(0, 1), glm::vec3(0.0f, -1.0f, 0.0f)));


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	this->orientation = glm::radians(orientation);
	this->offset = offset;
	this->scale = scale;
}
using namespace glm;

void CubeTextured::Update()
{
	//vec3 a = abs(offset - scale);
	//vec3 b = abs(camera.GetPosition());
	//float l = glm::length(b - a);
	//if (l < margin)
	//{
	//	float deltax = glm::length((camera.GetPosition()).x - (offset - scale).x);
	//	float deltay = glm::length((camera.GetPosition()).y - (offset - scale).y);
	//	float deltaz = glm::length((camera.GetPosition()).z - (offset - scale).z);
	//	glm::vec3 shiftCam;// = glm::vec3();

	//	if (deltax < margin) shiftCam.x = deltax - margin;
	//	if (deltay < margin) shiftCam.y = deltay - margin;
	//	if (deltaz < margin) shiftCam.z = deltaz - margin;
	//	if (shiftCam != glm::vec3())
	//	{
	//		camera.Translate(shiftCam * camera.cameraSpeed * fDeltaTime);
	//	}
	//}
	//offset = Lighting.gDiffuse;
}

void CubeTextured::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{

	glUseProgram(program);
	glBindVertexArray(vao);
	glm::mat4 rotate = glm::rotate(orientation.z, glm::vec3(0, 0, 1)); // z
	rotate = glm::rotate(rotate, orientation.x, glm::vec3(1, 0, 0)); // x
	rotate = glm::rotate(rotate, orientation.y, glm::vec3(0, 1, 0));
	glm::mat4 model_view = glm::translate(offset) * rotate * glm::scale(scale);
	glm::mat4 VP = projection_matrix*view_matrix;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture(TextureName));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1, false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "VP"), 1, false, &VP[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}