#pragma once
#include <vector>
#include <map>
#include "IGameObject.h"
#define FRONT	0x001
#define BACK	0x002
#define LEFT	0x004
#define RIGHT	0x008
#define TOP		0x010
#define BOTTOM	0x020
#define MASK	0x3F
namespace Rendering
{
	namespace Models
	{
		class Model :public IGameObject
		{
		public:
			Model();
			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix) override;
			virtual void Update() override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;
			virtual GLuint GetVao() const override;
			virtual const vector<GLuint>& GetVbos() const override;

			virtual const GLuint GetTexture(std::string textureName) const override;
			virtual void SetTexture(std::string textureName, GLuint texture) override;
		protected:
			GLuint vao;
			GLuint program;
			vector<GLuint> vbos;
			std::map<std::string, GLuint> textures;
		};
	}
}

