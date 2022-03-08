#pragma once
#include "Model.h"
#include <stdarg.h>

using namespace Rendering::Models;
namespace Rendering
{
	namespace Models
	{
		class QuadTextured : public Model
		{
		public:
			QuadTextured();
			~QuadTextured();

			void Create(glm::vec3& orientation, glm::vec3& offset,
				glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix)
				override final;
			virtual void Update() override final;
			string TextureName;
		private:
			vector<Rendering::VertexFormat> vertices;
			glm::vec3 orientation, rotation_speed;
			glm::vec3 scale, offset;
			GLfloat angle;
		};
	};
}
