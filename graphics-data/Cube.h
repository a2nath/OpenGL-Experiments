#pragma once
#include "Model.h"
#include <time.h>
#include <stdarg.h>
namespace Rendering
{
	namespace Models
	{
		class Cube : public Model
		{
		public:
			Cube();
			~Cube();

			void Create(glm::vec3& orientation, const GLuint& mask = MASK,
				glm::vec3& offset = glm::vec3(0, 0, 0),
				float alpha = 1.0f,
				glm::vec3& scale = glm::vec3(.25, .25, .25));

			virtual void Draw(const glm::mat4& projection_matrix,
							const glm::mat4& view_matrix)
							override final;
			virtual void Update() override final;
		private:
			vector<Rendering::VertexFormat> vertices;
			glm::vec3 orientation, rotation_speed;
			glm::vec3 scale, offset;
			GLuint mode;
			GLfloat angle, alpha;

			glm::vec3 eye_position;

			//material
			GLint material_shininess;
			GLfloat material_kd, material_ks,

			//attenuation
			att_kC, att_kL, att_kQ;
		};
	}
}