#pragma once
#include "Init_GLUT.h"
#include "Scene_Manager.h"

using namespace Core;
using namespace Init;
using namespace irrklang;
extern ISoundEngine* soundengine;

#define major	4
#define minor	0

int main(int argc, char **argv)
{
	/* lightFactor = emissive + ambient + diffuse + specular
	 emissive -> constant, object's own light
	 ambient -> Ka * ambientColor, Ka is the ambient reflection factor of the environment
	 diffuse -> Kd * lightColor * max(0,N·I), directly reaching light, Kd is the diffuse factor
	 N is the normal to the surface and I is the normalized inverted incidence vector
	 specular -> Ks * lightColor * max(N·H,0) ^ specularPower,
	 object's shiny surfaces that reflect a more focused light
	 http://iloveshaders.blogspot.ro/2011/04/how-lighting-works.html
	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
	*/
	/* Sound Enginge stuff*/
	std::cout << "*************************" << std::endl;

	// start the sound engine with default parameters
	soundengine = createIrrKlangDevice();

	if (!soundengine)
		return 0; // error starting up the engine

	WindowInfo window(std::string("TRON in OpenGL 4.0"),
		START_POSITION_X,START_POSITION_Y,WINDOW_WIDTH,WINDOW_HEIGHT, true);
	ContextInfo context(major, minor, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::Init(window, context, frameBufferInfo);

	Managers::Scene_Manager* scene = new Managers::Scene_Manager();
	Init_GLUT::SetListener(scene);
	Init_GLUT::Run();


	soundengine->drop(); // delete engine
	delete scene;
	return 0;
}
