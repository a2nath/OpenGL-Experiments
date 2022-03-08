#include "TransQuad.h"

using namespace Rendering::Models;
/*vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, +1.0f), this->color[3], glm::vec3(+0.0f, +1.0f, +0.0f)));
vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, -1.0f), this->color[0], glm::vec3(+0.0f, +1.0f, +0.0f)));
vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, -1.0f), this->color[1], glm::vec3(+0.0f, +1.0f, +0.0f)));
vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, +1.0f), this->color[2], glm::vec3(+0.0f, +1.0f, +0.0f)));*/
TransQuad::TransQuad()
{
	color = {
		{ 1.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f } };
}

TransQuad::~TransQuad()
{
}

void TransQuad::Create(glm::vec3 &orientation,
	glm::vec3 &offset,
	glm::vec3 &size,
	glm::mat4 &colors,int FACE)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	if (colors != glm::mat4())
		this->color = colors;

	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3,
		//4, 5, 6, 4, 6, 7
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// FRONT
	if (FACE & FRONT)
	{
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), this->color[0], glm::vec3(+0.0f, +0.0f, +1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), this->color[1], glm::vec3(+0.0f, +0.0f, +1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), this->color[2], glm::vec3(+0.0f, +0.0f, +1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), this->color[3], glm::vec3(+0.0f, +0.0f, +1.0f)));
	}
	// RIGHT
	if (FACE & RIGHT)
	{
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), this->color[0], glm::vec3(+1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), this->color[1], glm::vec3(+1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), this->color[2], glm::vec3(+1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), this->color[3], glm::vec3(+1.0f, 0.0f, +0.0f)));
	}
	// BACK
	if (FACE & BACK)
	{
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), this->color[0], glm::vec3(+0.0f, +0.0f, -1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), this->color[1], glm::vec3(+0.0f, +0.0f, -1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), this->color[2], glm::vec3(+0.0f, +0.0f, -1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), this->color[3], glm::vec3(+0.0f, +0.0f, -1.0f)));
	}
	// LEFT
	if (FACE & LEFT)
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), this->color[0], glm::vec3(-1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), this->color[1], glm::vec3(-1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), this->color[2], glm::vec3(-1.0f, 0.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), this->color[3], glm::vec3(-1.0f, 0.0f, +0.0f)));
	}
	// TOP
	if (FACE & TOP)
	{
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), this->color[0], glm::vec3(0.0f, +1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), this->color[1], glm::vec3(0.0f, +1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), this->color[2], glm::vec3(0.0f, +1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), this->color[3], glm::vec3(0.0f, +1.0f, +0.0f)));
	}

	// BOTTOM
	if (FACE & BOTTOM)
	{
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), this->color[0], glm::vec3(0.0f, -1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), this->color[1], glm::vec3(0.0f, -1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), this->color[2], glm::vec3(0.0f, -1.0f, +0.0f)));
		vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), this->color[3], glm::vec3(0.0f, -1.0f, +0.0f)));
	}

	/*vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, -1.0f), this->color[0], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, -1.0f), this->color[1], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, +1.0f), this->color[2], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, +1.0f), this->color[3], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, +1.0f), this->color[3], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, -1.0f), this->color[0], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, -1.0f), this->color[1], glm::vec3(+0.0f, +1.0f, +0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, +1.0f), this->color[2], glm::vec3(+0.0f, +1.0f, +0.0f)));*/

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);
	angle = glm::radians(1.0f);
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
	this->orientation = angle + glm::radians(orientation);
	this->offset = offset;
	this->scale = size == glm::vec3() ? glm ::vec3(1.0f) : size ;
	this->indicesCount = indices.size();
}
void TransQuad::Update()
{
	orientation = 0.0009f + orientation;
}

void TransQuad::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glm::mat4 rotate = glm::rotate(orientation.z, glm::vec3(0, 0, 1));
	rotate = glm::rotate(rotate, orientation.x, glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, orientation.y, glm::vec3(0, 1, 0));
	glm::mat4 model_view = glm::translate(offset) * rotate * glm::scale(scale);
	glm::mat4 VP = projection_matrix*view_matrix;

	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1, false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "VP"), 1, false, &VP[0][0]);
	if ((color[0]).z != 1.0f) glDepthMask(0);
	//glCullFace(GL_BACK);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0); //draw front
	//glCullFace(GL_FRONT);
	//glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint))); //draw back
	if ((color[0]).z != 1.0f) glDepthMask(1);
}