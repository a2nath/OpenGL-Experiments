#pragma once
#include "Model.h"

namespace Rendering
{
	namespace Models
	{
		class Quad : public Models::Model
		{
		public:
			Quad();
			~Quad();

			/* Orientation | Offset (0 0 0) | Size (1 1 1) | Colors (defaults) */
			void Create(glm::vec3 &,
				glm::vec3& offset = glm::vec3(),
				glm::vec3& scaling = glm::vec3(1.0f),
				glm::mat4& color = glm::mat4());
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix);
			virtual void Update() override final;
		private:
			glm::vec3 orientation, rotation_speed;
			glm::vec3 scale, offset;
			GLfloat angle, alpha, indicesCount;
			glm::mat4 color;
		};
	}
}