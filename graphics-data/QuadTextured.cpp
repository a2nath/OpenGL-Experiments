#include "QuadTextured.h"

using namespace Rendering::Models;

QuadTextured::QuadTextured()
{
}

QuadTextured::~QuadTextured()
{
}

void QuadTextured::Create(glm::vec3 &orientation, glm::vec3 &offset, glm::vec3 &size)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3 };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +0.0f, +1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +0.0f, +1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	//nothing different from Triangle model
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);            //here we have 4
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

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
	this->scale = size;
}
void QuadTextured::Update()
{
}

void QuadTextured::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glm::mat4 rotate = glm::rotate(orientation.z, glm::vec3(0, 0, 1)); // z
	rotate = glm::rotate(rotate, orientation.x, glm::vec3(1, 0, 0)); // x
	rotate = glm::rotate(rotate, orientation.y, glm::vec3(0, 1, 0));
	glm::mat4 model_view = glm::translate(offset) * rotate * glm::scale(scale);
	glm::mat4 VP = projection_matrix*view_matrix;;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture(TextureName));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1,
		false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "VP"), 1,
		false, &VP[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}