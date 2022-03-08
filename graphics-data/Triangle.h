#pragma once
#include "Model.h"
namespace Rendering
{
	namespace Models
	{
		class Triangle: public Model
		{
		public:
			Triangle();
			~Triangle();
			void Create(glm::vec3& orient);
			virtual void Draw(const glm::mat4& projection_matrix,
				const glm::mat4& view_matrix) override final;
			virtual void Update() override final;

		private:
			glm::vec3 orientation, rotation_speed;
			glm::vec3 scale, offset;
		};

	}
}

