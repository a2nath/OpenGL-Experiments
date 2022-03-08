#include "Line.h"

using namespace Rendering;
using namespace Models;

Line::Line()
{
	//light_position = glm::vec3(0, 0, 50);
	//eye_position = glm::vec3(50, 0, 50);

	//material_shininess = 100;
	//material_kd = .5;
	//material_ks = .3;

	////attenuation
	//att_kC = 0,
	//att_kL = 0,
	//att_kQ = 0.0002;
}

Line::~Line()
{
}

void Line::Create(glm::vec3 &orientation, glm::vec3 &offset, int &slant)
{
	// this code will be used in the next tutorial in CreateTriangleModel method
	GLuint vao;	 //our VAO handler
	GLuint vbo;  //our vbo handler
	//VAO
	glGenVertexArrays(1, &vao);  //create VAO container and get ID for it
	glBindVertexArray(vao);      //bind to OpenGL context

	GLfloat indice = 0.01f;
	glm::vec2 lower = (slant) ? glm::vec2(0.0f, -.25f) : glm::vec2(-.25f, 0.0f);
	glm::vec2 upper = (slant) ? glm::vec2(0.0f, .25f) : glm::vec2(.25f, 0.0f);
	vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-indice, lower),
		glm::vec4(0.0941, 0.792, 0.902, 1)));
		//glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-indice, upper), //upper-left
		glm::vec4(0.0941, 0.792, 0.902, 1)));
	vertices.push_back(VertexFormat(glm::vec3(indice, lower), //lower-right
		glm::vec4(0.0941, 0.792, 0.902, 1)));
	vertices.push_back(VertexFormat(glm::vec3(indice, upper), //upper-right
		glm::vec4(0.0941, 0.792, 0.902, 1)));

	//now that VAO is binded to context we can reference our buffer(s)
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//bind to context
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//buffer is binded to context,set pipes:)
	glEnableVertexAttribArray(0); //being used for vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1); //being used for vertex colours!
	// you can use offsetof to get the offset of an attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->slant = slant;
	this->offset = offset;
	this->orientation = glm::radians(orientation);
	scale = { 1, 1, 1 };
}

void Line::Update()
{	
	if (scale.x <= 25.0)
	{
		scale.x += (float)(1.0 / 32.0);
	}
}

void Line::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glm::mat4 rotate = glm::rotate(orientation.y, glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate,orientation.x, glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, orientation.z, glm::vec3(0, 0, 1));
	
	glm::mat4 model_view = rotate * glm::translate(offset) * glm::scale(scale);
	glm::mat4 MVP = projection_matrix*view_matrix*model_view;
	glUseProgram(program);

	/* Fragment Shader uniform parameters */
	/*glUniform3fv(glGetUniformLocation(program, "light_position"), 1, &light_position[0]);
	glUniform3fv(glGetUniformLocation(program, "eye_position"), 1, &eye_position[0]);
	glUniform1i(glGetUniformLocation(program, "material_shininess"), material_shininess);
	glUniform1f(glGetUniformLocation(program, "material_kd"), material_kd);
	glUniform1f(glGetUniformLocation(program, "material_ks"), material_ks);
	glUniform1f(glGetUniformLocation(program, "att_kC"), att_kC);
	glUniform1f(glGetUniformLocation(program, "att_kL"), att_kL);
	glUniform1f(glGetUniformLocation(program, "att_kQ"), att_kQ);
	*/
	/* Vertex Shader uniform parameters */
	glUniformMatrix4fv(glGetUniformLocation(program, "model_view"), 1,
		false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1,
		false, &MVP[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}