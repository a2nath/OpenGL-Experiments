#include "Cube.h"

using namespace Rendering::Models;

float rotation_rate = 0.0009;
Cube::Cube()
{

	//material_shininess = 100;
	//material_kd = .5;
	//material_ks = .3;

	////attenuation
	//att_kC = 0,
	//att_kL = 0,
	//att_kQ = 0.0002;
}


Cube::~Cube()
{
}
// Draw cube with parameters: orientation, face_config, offset, scale
void Cube::Create(glm::vec3 &orientation,
	const GLuint& face_info,
	glm::vec3 &offset,
	float alpha,
	glm::vec3 &scale)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	std::vector<unsigned int> indices = {
		0,  1,  2,  0,  2,  3,    //front
		4,  5,  6,  4,  6,  7,    //right
		8,  9,  10, 8,  10, 11,   //back
		12, 13, 14, 12, 14, 15,   //left
		16, 17, 18, 16, 18, 19,   //upper
		20, 21, 22, 20, 22, 23,  //bottom

		//26, 24, 25, 27, 24, 26,
		//30, 28, 29, 31, 38, 30,
		//34, 32, 33, 35, 32, 34,
		//38, 36, 37, 39, 36, 38,
		//42, 40, 41, 42, 40, 41,
		//46, 44, 45, 47, 44, 46
	};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec4(0.0f, 0.0f, 1.0f, alpha), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec4(1.0f, 0.0f, 1.0f, alpha), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec4(1.0f, 1.0f, 1.0f, alpha), glm::vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec4(0.0f, 1.0f, 1.0f, alpha), glm::vec3(0.0f, 0.0f, 1.0f)));

	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec4(1.0f, 0.0f, 1.0f, alpha), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 0.0f, 0.0f, alpha), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 0.0f, alpha), glm::vec3(1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec4(1.0f, 1.0f, 1.0f, alpha), glm::vec3(1.0f, 0.0f, 0.0f)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, alpha), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 0.0f, alpha), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 0.0f, 0.0f, alpha), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(0.0f, 0.0f, 0.0f, alpha), glm::vec3(0.0f, 0.0f, -1.0f)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(0.0f, 0.0f, 0.0f, alpha), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec4(0.0f, 0.0f, 1.0f, alpha), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec4(0.0f, 1.0f, 1.0f, alpha), glm::vec3(-1.0f, 0.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, alpha), glm::vec3(-1.0f, 0.0f, 0.0f)));

	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 0.0f, alpha), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec4(0.0f, 1.0f, 0.0f, alpha), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec4(0.0f, 1.0f, 1.0f, alpha), glm::vec3(0.0f, 1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec4(1.0f, 1.0f, 1.0f, alpha), glm::vec3(0.0f, 1.0f, 0.0f)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(0.0f, 0.0f, 0.0f, alpha), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 0.0f, 0.0f, alpha), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec4(1.0f, 0.0f, 1.0f, alpha), glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec4(0.0f, 0.0f, 1.0f, alpha), glm::vec3(0.0f, -1.0f, 0.0f)));

	vector<VertexFormat> temp;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

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
	this->scale = scale;
	this->alpha = alpha;
}

void Cube::Update()
{
	orientation = rotation_rate + orientation;
	if (abs(glm::length(camera.GetPosition() - offset)) < .25f) {
		offset.y = -100;
	}
}

void Cube::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glm::mat4 rotate = glm::rotate(orientation.z, glm::vec3(0, 0, 1)); // z
	rotate = glm::rotate(rotate, orientation.x, glm::vec3(1, 0, 0)); // x
	rotate = glm::rotate(rotate, orientation.y, glm::vec3(0, 1, 0));
	glm::mat4 model_view = glm::translate(offset) * rotate * glm::scale(scale);
	glm::mat4 VP = projection_matrix*view_matrix;
	glm::vec3 diffusePosition = glm::vec3(offset.x, offset.y - .5f, offset.z);

	glUniformMatrix4fv(glGetUniformLocation(program, "MV"), 1, false, &model_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "VP"), 1, false, &VP[0][0]);
	glUniform4fv(glGetUniformLocation(program, "ambientLight"), 1, &(Lighting.gAmbient)[0]);
	glUniform3fv(glGetUniformLocation(program, "lightPositionWorld"), 1, &diffusePosition[0]);
	glUniform1i(glGetUniformLocation(program, "flashon"), Lighting.flashon);
	glUniform3fv(glGetUniformLocation(program, "eyePositionWorld"), 1, &(camera.GetPosition())[0]);
	if (alpha != 1) glDepthMask(0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	if (alpha != 1) glDepthMask(1);
}