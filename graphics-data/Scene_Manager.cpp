#include "Scene_Manager.h"
using namespace Managers;

Managers::Camera camera;
Core::Init::Light Lighting;

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	/*0*/ AddShaders("colorShader", "Vertex_Shader", "Fragment_Shader");
	/*1*/ AddShaders("textureShader", "Vertex_Shader_Texture", "Fragment_Shader_Texture");
	/*2*/ AddShaders("textureShader_light", "Vertex_Shader_Texture_Lighting", "Fragment_Shader_Texture_Lighting");
	/*3*/ AddShaders("MultiTexSphereShader", "Vertex_Shader_Texture", "MultiTexSphere_Fragment");
	/*4*/ AddShaders("lightcube", "vlightcube", "flightcube");

	view_matrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	models_manager = new Models_Manager(shaders);
}

Scene_Manager::~Scene_Manager()
{

	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::NotifyBeginFrame()
{
	models_manager->Update();
}

void Scene_Manager::AddShaders(string shadername, string vShaderName, string fShaderName)
{
	shader_manager = new Shader_Manager();
	shader_manager->CreateProgram(shadername, "Shaders\\" + vShaderName + ".glsl", "Shaders\\" + fShaderName + ".glsl");
	shaders.push_back(shadername);
}

void Scene_Manager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	//glEnable(GL_BLEND);											// added for multitexturing tutorial
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	models_manager->Draw();
	models_manager->Draw(projection_matrix,
					camera.GetViewMatrix() * glm::toMat4(camera.g_Rotation));
}

void Scene_Manager::NotifyEndFrame()
{

}

void Scene_Manager::NotifyReshape(int width, int height)
{
	float FOV = 45.0f, near1 = 0.1f, far1 = 200.0f;
	float aspect_ratio = (float)width / (float)height;
	camera.SetViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	projection_matrix = glm::perspective(FOV, aspect_ratio, near1, far1);

}

Managers::Models_Manager* Scene_Manager::GetModels_Manager()
{
	return models_manager;
}