#include "GameModels.h"
#include "Core\Shader_Manager.h"
using namespace Models;
using namespace Rendering;
GameModels::GameModels()
{
}


GameModels::~GameModels()
{
	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		//delete VAO and VBOs (if many)
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModels::CreateTriangleModel(const string &gameModelName)
{
	// this code will be used in the next tutorial in CreateTriangleModel method
	unsigned int vao;            //our VAO handler
	unsigned int vbo; //our vbo handler
	//VAO
	glGenVertexArrays(1, &vao);  //create VAO container and get ID for it
	glBindVertexArray(vao);      //bind to OpenGL context

	//triangle vertices on stack
	vector<VertexFormat> vertices;
	//specify vertex positions
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), 
									glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0), 
									glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0),
									glm::vec4(0, 0, 1, 1)));
	
	//now that VAO is binded to context we can reference our buffer(s)
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//bind to context
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	//buffer is binded to context,set pipes:)
	glEnableVertexAttribArray(0); //being used for vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0); 
	glEnableVertexAttribArray(1); //being used for vertex colours!
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);
	//Tell OpenGL about our data format

	Model myModel;                            //is allocated on Stack
	myModel.vao = vao;                        //add vao
	myModel.vbos.push_back(vbo);              //add vbo
	GameModelList[gameModelName] = myModel;  //add to std::map

}

void GameModels::DeleteModel(const string& gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}
unsigned int GameModels::GetModel(const std::string& gameModelName)
{
	return GameModelList[gameModelName].vao;
}

/*

void GameModels::CreateTriangleModel(const std::string& gameModelName)
{
unsigned int vao;
unsigned int vbo;

glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

std::vector<VertexFormat> vertices;//our vertex positions
vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0)));
vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0)));
vertices.push_back(VertexFormat(glm::vec3( 0.25, 0.25, 0.0)));

glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

Model myModel;                            //is allocated on Stack
myModel.vao = vao;                        //add vao
myModel.vbos.push_back(vbo);              //add vbo
GameModelList[gameModelName] = myModel;  //add to std::map

}*/