#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Core
{
	namespace Init
	{
		struct Light
		{
			glm::vec3 reset;
			glm::vec3 gDiffuse;
			glm::vec4 gAmbient;
			GLint mSpecExp;
			int flashon;
			Light() :gAmbient(.3f, .3f, .3f, 1.0f),
				mSpecExp(50),
				gDiffuse(0, 2, 0),
				flashon(1)
			{
			}
			void SetDiffuseInitial(glm::vec3 initial_gDiffuse)
			{
				reset = initial_gDiffuse;
			}
			void toggleflash()
			{
				flashon = flashon ? 0 : 1;
			}

			void setSpecularExp(int i)
			{
				if (mSpecExp + i <= 56 && mSpecExp + i >= -10)
					mSpecExp += i;
			}
			GLuint getSpecularExp()
			{
				return mSpecExp;
			}
			void Reset()
			{
				gDiffuse = reset;
				gAmbient = glm::vec4(.3f, .3f, .3f, 1.0f),
				mSpecExp = 50;
			}

			void setAmbeint(float x, float y = -1, float z = -1)
			{
				if (!(gAmbient.x + x < 0.0f) || !(gAmbient.x + x > 10.0f))
				{
					if (!(y < 0))
						gAmbient = glm::vec4(x, y, z, 1);
					else
						gAmbient = glm::vec4(x, x, x, 1);
				}
				else {
					cout << "Ambient intensity at limits" << endl;
				}
			}
		};
	};
};
extern Core::Init::Light Lighting;