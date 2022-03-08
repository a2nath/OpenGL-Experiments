#include "Init_GLEW.h"
using namespace Core;
using namespace Core::Init;


void Init_GLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initialized" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_0"))
	{
		std::cout << "GLEW GL_VERSION_4_0 is 4.0\n ";
	}
	else
	{
		std::cout << " GLEW GL_VERSION_4_0 not supported\n ";
	}
}
Init_GLEW::Init_GLEW()
{
}


Init_GLEW::~Init_GLEW()
{
}
