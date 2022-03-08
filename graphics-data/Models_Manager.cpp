#include "Models_Manager.h"
#include "SOIL.h"

using namespace Managers;
irrklang::ISoundEngine* soundengine;
int object_count = 0;
TextureLoader* ptexture;
string texturetype;
Models::DiffuseLight *cam;
Models::CubeTextured *tcube;
Models::QuadTextured *tquad;
Models::Multitexturing* multitexSphere;
GLuint prog;

void cameraset(glm::vec3 offset)
{
	camera.SetPosition(camera.GetPosition() + offset, 1);
}
void Models_Manager::Flashlight(GLuint prog)
{
	cam = new Models::DiffuseLight();
	cam->SetProgram(prog);
	cam->Create();
	gameModelList.push_back(cam);
}
void cubemaze(std::map<std::string, IGameObject*> &game, const int &M, const int &N)
{
	Models::Cube* cube;
	vector<vector< GLfloat> > locs;

	if (M*N == 9)
		locs = {
				{ -.5, -.5, 0 }, { -.5, 0, 0 }, { 0, -.5, 0 }, { 0, 0, 0 }, { .5, -.5, 0 },
				{ -.5, .5, 0 }, { .5, 0, 0 }, { 0, .5, 0 }, { .5, .5, 0 }
		};

	int debug = 0;

	GLuint faceConfig[] = {
		BACK | BOTTOM | TOP,			//a
		TOP | BOTTOM | BACK,			//b
		BACK| TOP,					//c
		BACK | BOTTOM | RIGHT | TOP,	//d
		TOP | RIGHT,					//e
		BACK,							//f
		BOTTOM | TOP,					//g
		BACK | BOTTOM | RIGHT,			//h
		BOTTOM | TOP					//i
	};

	if (debug){
		for (auto face : faceConfig)
		{
			face |= FRONT;
		}
	}

	for (GLuint tile = 0; tile < M*N; tile++)
	{
		cube = new Models::Cube();
		cube->SetProgram(Shader_Manager::GetShader("colorShader"));
		cube->Create(glm::vec3(-90.0f, 0.0f, 0.0f),
			MASK & ~(faceConfig[tile]),
			glm::vec3(locs[tile][0] * 4, locs[tile][1] * 4, locs[tile][2] * 4));
		game["t" + std::to_string(tile)] = cube;
	}
}
void makeCube(std::vector<IGameObject*> &game, glm::vec3 offset, float alpha = 1.0f, glm::vec3 scaling = glm::vec3(.25f))
{
	Models::Cube *cube = new Models::Cube();
	cube->SetProgram(Shader_Manager::GetShader("colorShader"));
	cube->Create(glm::vec3(0.0f), MASK, offset, alpha, scaling);
	game.push_back(cube);
}
void makePlane(std::vector<IGameObject*> &game, glm::vec3 offset, float orientation = 0.0f, glm::mat4 colors = glm::mat4())
{
	Models::Quad *quad = new Models::Quad();
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create(glm::vec3(orientation), offset, glm::vec3(0.75f), colors);
	game.push_back(quad);
}

void Models_Manager::TextureCube(GLuint &program, glm::vec3 offset, string& texttype, glm::vec3& scale)
{
	ptexture = new TextureLoader();
	unsigned int texture = ptexture->LoadTexture("Textures\\" + texttype + ".bmp", 350, 350);
	tcube = new Models::CubeTextured();
	tcube->SetProgram(program);
	tcube->Create(glm::vec3(), offset, scale);
	tcube->TextureName = texttype;
	tcube->SetTexture(tcube->TextureName, texture);
	gameModelList.push_back(tcube);
}
void Models_Manager::TextureQuad(GLuint &program, glm::vec3 orient, glm::vec3 offset, string& texttype, glm::vec3& scale)
{
	ptexture = new TextureLoader();
	unsigned int texture = ptexture->LoadTexture("Textures\\" + texttype + ".bmp", 350, 350);
	tquad = new Models::QuadTextured();
	tquad->SetProgram(program);
	tquad->Create(orient, offset, scale);
	tquad->TextureName = texttype;
	tquad->SetTexture(tquad->TextureName, texture);
	gameModelList.push_back(tquad);
}
void Models_Manager::Globe(GLuint& program, glm::vec3 offset)
{
	multitexSphere = new Multitexturing();
	multitexSphere->SetProgram(program);
	multitexSphere->CreateSphere(.25, 24, 48, offset);	//generate sphere geometry and bind ibo, vbo buffers.

														// Make sure SOIL_FLAG is set to repeat since we will be "scrolling" the UV coordinates
	multitexSphere->SetTexture("BaseTexture", SOIL_load_OGL_texture("Textures\\nebula1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("SecondTexture", SOIL_load_OGL_texture("Textures\\nebula2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("ThirdTexture", SOIL_load_OGL_texture("Textures\\nebula3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("AlphaChanTexture", SOIL_load_OGL_texture("Textures\\alphaChan.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	multitexSphere->SetTexture("RampTexture", SOIL_load_OGL_texture("Textures\\ramp.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	gameModelList.push_back(multitexSphere);
}
void Models_Manager::buildglobes()
{
	prog = Shader_Manager::GetShader(shaders[3]);

	Globe(prog, glm::vec3(-4.5f, +0.5f, -2.5f));
	Globe(prog, glm::vec3(+0.5f, +0.5f, +1.5f));
	Globe(prog, glm::vec3(+0.5f, +0.5f, +3.5f));
}
void Models_Manager::buildcrates()
{

	prog = Shader_Manager::GetShader(shaders[2]);
	Flashlight(prog);
	texturetype = "circuit";

	//quad 1
	TextureCube(prog, glm::vec3(+0.5f, +0.5f, -0.5f), texturetype);
	TextureCube(prog, glm::vec3(+0.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(+0.5f, +0.5f, -3.5f), texturetype);
	TextureCube(prog, glm::vec3(+2.5f, +0.5f, -1.5f), texturetype);
	TextureCube(prog, glm::vec3(+2.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(+3.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(+4.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(+4.5f, +0.5f, -0.5f), texturetype);

	//quad 2
	TextureCube(prog, glm::vec3(-0.5f, +0.5f, -0.5f), texturetype);
	TextureCube(prog, glm::vec3(-3.5f, +0.5f, -1.5f), texturetype);
	TextureCube(prog, glm::vec3(-3.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(-2.5f, +0.5f, -2.5f), texturetype);
	TextureCube(prog, glm::vec3(-4.5f, +0.5f, -3.5f), texturetype);
	TextureCube(prog, glm::vec3(-0.5f, +0.5f, -2.5f), texturetype);

	//quad 4
	TextureCube(prog, glm::vec3(+0.5f, +0.5f, +0.5f), texturetype);
	TextureCube(prog, glm::vec3(+0.5f, +0.5f, +2.5f), texturetype);
	TextureCube(prog, glm::vec3(+1.5f, +0.5f, +2.5f), texturetype);
	TextureCube(prog, glm::vec3(+2.5f, +0.5f, +0.5f), texturetype);
	TextureCube(prog, glm::vec3(+2.5f, +0.5f, +1.5f), texturetype);
	TextureCube(prog, glm::vec3(+3.5f, +0.5f, +1.5f), texturetype);
	TextureCube(prog, glm::vec3(+3.5f, +0.5f, +3.5f), texturetype);

	//quad3
	TextureCube(prog, glm::vec3(-0.5f, +0.5f, +3.5f), texturetype);
	TextureCube(prog, glm::vec3(-1.5f, +0.5f, +1.5f), texturetype);
	TextureCube(prog, glm::vec3(-3.5f, +0.5f, +2.5f), texturetype);
	TextureCube(prog, glm::vec3(-3.5f, +0.5f, +3.5f), texturetype);
	TextureCube(prog, glm::vec3(-2.5f, +0.5f, +3.5f), texturetype);
	TextureCube(prog, glm::vec3(-3.5f, +0.5f, +0.5f), texturetype);
	TextureCube(prog, glm::vec3(-4.5f, +0.5f, +0.5f), texturetype);
}
void Models_Manager::buildfloor()
{
	prog = Shader_Manager::GetShader("textureShader");
	texturetype = "tilex1";
	int rows = 8;
	int col = 10;
	float offsetx = -rows / 2;
	float offsety = -col / 2;
	for (float i = offsetx+.5; i < rows + offsetx; i++)
	{
		for (float j = offsety+.5; j < col + offsety; j++)
		{
			TextureQuad(prog, glm::vec3(), glm::vec3(j, 0.0f, i), texturetype);
		}
	}
}
void Models_Manager::placepowers()
{
	prog = Shader_Manager::GetShader("colorShader");
	makeCube(gameModelList, glm::vec3(-4.5f, +.5f, -2.5f), .5f, glm::vec3(.25f));
	makeCube(gameModelList, glm::vec3(+0.5f, +.5f, +1.5f), .5f, glm::vec3(.25f));
	makeCube(gameModelList, glm::vec3(+0.5f, +.5f, +3.5f), .5f, glm::vec3(.25f));
}
void Models_Manager::PlayTRON()
{
	printf("Loading maze\n");
	buildcrates();
	printf("Putting down floors\n");
	buildfloor();
	printf("Creating power-ups\n");
	placepowers();
	printf("Placing walls");
	soundengine->play2D("Sound\\tronlegacy.mp3");
	std::cout << "Playing Track: Tron Legacy Theme Song" << std::endl;
	std::cout << "*************************" << std::endl;
}

void Models_Manager::HyperTransparentCube()
{
	Models::TransQuad *quad;
	glm::mat4
	colors = {
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f } };

	//back
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, BACK);
	gameModelList.push_back(quad);

	colors = {
		{ 0.0f, 0.7f, 0.4f, .9f },
		{ 0.0f, 0.7f, 0.4f, .9f },
		{ 0.0f, 0.7f, 0.4f, .9f },
		{ 0.0f, 0.7f, 0.4f, .9f } };

	//right
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, RIGHT);
	gameModelList.push_back(quad);

	colors = {
		{ 0.2f, 0.0f, 0.7f, .8f },
		{ 0.2f, 0.0f, 0.7f, .8f },
		{ 0.2f, 0.0f, 0.7f, .8f },
		{ 0.2f, 0.0f, 0.7f, .8f } };

	//top
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, TOP);
	gameModelList.push_back(quad);

	colors = {
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f } };

	//////left
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, LEFT);
	gameModelList.push_back(quad);

	colors = {
		{1.0f, 0.0f, 0.0f, .1f },
		{1.0f, 0.0f, 0.0f, .1f },
		{1.0f, 0.0f, 0.0f, .1f },
		{1.0f, 0.0f, 0.0f, .1f } };

	//bottom
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, BOTTOM);
	gameModelList.push_back(quad);

	colors = {
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f },
		{ 0.5f, 0.0f, 0.7f, .5f } };
	// front
	quad = new Models::TransQuad();
	quad->SetProgram(Shader_Manager::GetShader(shaders[0]));
	quad->Create(glm::vec3(), glm::vec3(), glm::vec3(), colors, FRONT);
	gameModelList.push_back(quad);

}

void Models_Manager::createmodels()
{
	camera.SetPosition(glm::vec3(0.0f,0.0f,2.0f), 1);
	Lighting.SetDiffuseInitial(glm::vec3(0.0f, 2.0f, 0.0f));
	Lighting.setAmbeint(.3f);

	//string type = "circuit";
	//GLuint
	///prog = Shader_Manager::GetShader(shaders[1]);
	//TextureQuad(prog, glm::vec3(90.0f,0.0f,0.0f), glm::vec3(0,0,-1), type, glm::vec3(.5f));


	PlayTRON();

	//string type = "circuit";
	//prog = Shader_Manager::GetShader(shaders[1]);
	//TextureCube(prog, glm::vec3(), type, glm::vec3(0.05f));

	// for the plane behind
	//prog = Shader_Manager::GetShader(shaders[0]);
	//Flashlight(prog);
	///makePlane(gameModelList, glm::vec3(0.0f, 0.0f, -2.0f), 90);
	//HyperTransparentCube();
	//makeCube(gameModelList, glm::vec3(-2.0f, 0.0f, 0.0f), 0.5f);

	// super transparent cube
	//prog = Shader_Manager::GetShader(shaders[4]);
	//Flashlight(prog);

	//prog = Shader_Manager::GetShader(shaders[1]);
	//TextureCube(prog, glm::vec3(), type, glm::vec3(0.0125f));

	//prog = Shader_Manager::GetShader(shaders[0]);
	//Flashlight(prog);

	/*
	Flashlight(shaders[1]);
	makePlane(gameModelList, glm::vec3(0.0f, 0.0f, -2.0f), 90);

	prog = Shader_Manager::GetShader("textureShader");
	string type = "circuit";
	TextureCube(prog, Lighting.gDiffuse, type, glm::vec3(0.0125));
	makeCube(gameModelList, glm::vec3(0.0f, 0.0f, 1.0f));
	PlayTRON();
		/* =========== to test globe ============== */
		/*glDepthMask(0);
		Models::CubeTextured* cube = new CubeTextured();
		prog = Shader_Manager::GetShader("MultiTexSphereShader");
		cube->SetProgram(prog);
		cube->Create(glm::vec3(0,0,0));
		cube->TextureName = "Create";
		cube->SetTexture("Create", SOIL_load_OGL_texture("Textures\\Crate.bmp", SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS));
		gameModelList["cube"] = cube;
		glDepthMask(1);

	*/


	/*prog = Shader_Manager::GetShader("MultiTexSphereShader");

	Globe(prog, glm::vec3(0.0f, 0.0f, 0.0f));

	*/

	/*
	glm::vec3 scaling(5.0f, 5.0f, 5.0f);
	Models::Quad *quad = new Models::Quad();
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create(glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(+0.0f, -0.0f, +0.0f),
		scaling);
	gameModelList["plane"] = quad;
	*/

	//makePlane(gameModelList, glm::vec3(+00.0f, -2.0f, +0.0f),1);
	//makeCube(gameModelList, glm::vec3(+0.0f,+0.0f, +0.0f));

	//prog = Shader_Manager::GetShader("MultiTexSphereShader");

	//Globe(prog, glm::vec3(0.0f, 0.0f, -1.0f));
	//printf("Starting...\n");

}
Models_Manager::Models_Manager(vector<string> shaders)
{
	this->shaders = shaders;
	createmodels();
}

Models_Manager::~Models_Manager()
{

	for (auto model: gameModelList)
	{
		delete model;
	}
	gameModelList.clear();

	for (auto model : gameModelList_NDC)
	{
		delete model;
	}
	gameModelList_NDC.clear();
	delete ptexture;
}

void Models_Manager::Update()
{
	for (auto model: gameModelList)
	{
		model->Update();
	}
	for (auto model : gameModelList_NDC)
	{
		model->Update();
	}
}

//NDC
void Models_Manager::Draw()
{
	for (auto model : gameModelList_NDC)
	{
		model->Draw();
	}
}

void Models_Manager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto model : gameModelList)
	{
		model->Draw(projection_matrix, view_matrix);
	}
}

void Models_Manager::DeleteModel(IGameObject* model)
{
	auto iterator = find(gameModelList.begin(), gameModelList.end(), model);
	(*iterator)->Destroy();
	gameModelList.erase(iterator);
}

void Models_Manager::DeleteModel_NDC(IGameObject* model)
{

	auto iterator = find(gameModelList_NDC.begin(), gameModelList_NDC.end(), model);
	(*iterator)->Destroy();
	gameModelList_NDC.erase(iterator);
}

void Models_Manager::SetModel(IGameObject* oldobject, IGameObject* newobject)
{
	//gameModelList[gameObjectName.c_str()] = gameObject;
	auto iterator = std::find(gameModelList.begin(), gameModelList.end(), oldobject);
	(*iterator) = newobject;
}

