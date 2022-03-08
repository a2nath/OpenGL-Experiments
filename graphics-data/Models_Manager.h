#pragma once
#include <unordered_map>
#include "Shader_Manager.h"
#include "IGameObject.h"
#include "Textures.h"
#include "Triangle.h"
#include "Quad.h"
#include "Cube.h"
#include "CubeTextured.h"
#include "QuadTextured.h"
#include "DiabloGlobe.h"
#include "DiffuseLight.h"
#include "TransQuad.h"

using namespace Rendering;

namespace Managers
{
	class Models_Manager
	{
	public:
		Models_Manager(vector<string> shadersList);
		~Models_Manager();

		void Draw();
		void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		void Update();

		void DeleteModel(IGameObject* modelsList);
		void DeleteModel_NDC(IGameObject* modelsListNDC);

		void SetModel(IGameObject* old_gameObject, IGameObject* new_gameObject);
		void TextureQuad(GLuint &program, glm::vec3 orientation, glm::vec3 offset, string& texttype, glm::vec3& scale = glm::vec3(0.5f));
		void TextureCube(GLuint &program, glm::vec3 offset, string& texttype, glm::vec3& scale = glm::vec3(0.5f));
		void Globe(GLuint &program, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
		void buildfloor();
		void buildcrates();
		void buildglobes();
		void Flashlight(GLuint program);
		void PlayTRON();
		void createmodels();
		void placepowers();
		void HyperTransparentCube();
	private:
		vector<string> shaders;
		std::vector<IGameObject* > gameModelList;
		std::vector<IGameObject* > gameModelList_NDC;
	};
}
