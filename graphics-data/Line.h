#pragma once
#include "Model.h"
namespace Rendering
{
	namespace Models
	{
		class Line : public Model
		{
		public:
			Line();
			~Line();
			// glm::vec3 orientation of the object, glm::vec3 offset from the original position
			void Create(glm::vec3 &orientation, int &slant,
				glm::vec3& offset = glm::vec3(0, 0, 0),
				glm::vec3& scaling = glm::vec3(1, 1, 1));
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix)
				override final;
			virtual void Update() override final;
		private:
			glm::vec3 rotation, rotation_speed;
			glm::vec3 scale, angle, orientation, offset;
			int slant;

			glm::vec3 light_position, eye_position;

			//material
			GLint material_shininess;
			GLfloat material_kd, material_ks,

			//attenuation
			att_kC, att_kL, att_kQ;
		};
	}
}