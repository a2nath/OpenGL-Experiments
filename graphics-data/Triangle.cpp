#include "Triangle.h"

using namespace Rendering;
using namespace Models;

Triangle::Triangle(){}

Triangle::~Triangle(){}

void Triangle::Create(glm::vec3& orientation)
{
	unsigned int vao;            //our VAO handler
	unsigned int vbo; //our vbo handler
	//VAO
	glGenVertexArrays(1, &vao);  //create VAO container and get ID for it
	glBindVertexArray(vao);      //bind to OpenGL context

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(1, 0, 0, 1), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0),	glm::vec4(0, 1, 0, 1), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), glm::vec4(0, 0, 1, 1), glm::vec3(0.0f, 1.0f, 0.0f)));

	//now that VAO is binded to context we can reference our buffer(s)
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//bind to context
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1); //being used for vertex colours!
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2); //being used for vertex colours!
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),(void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->orientation = orientation;

}

void Triangle::Update()
{
}

void Triangle::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glm::mat4 rotate = glm::rotate(orientation.y, glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, orientation.x, glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, orientation.z, glm::vec3(0, 0, 1));

	glm::mat4 model_view = glm::translate(offset) * rotate * glm::scale(scale);
	glm::mat4 VP = projection_matrix*view_matrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1, false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "VP"), 1, false, &VP[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}