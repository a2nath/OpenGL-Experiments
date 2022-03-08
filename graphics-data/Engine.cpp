#include "Engine.h"

using namespace std;
using namespace Core;
using namespace Init;
using namespace irrklang;
extern ISoundEngine* soundengine;

#define major	4
#define minor	0

Engine::Engine()
{
}

bool Engine::Init()
{
	WindowInfo window(std::string("TRON in OpenGL 4.0"),
		START_POSITION_X, START_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ContextInfo context(major, minor, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);

	Init_GLUT::Init(window, context, frameBufferInfo);

	scene_manager = new Managers::Scene_Manager();
	Init_GLUT::SetListener(scene_manager);
	//start the sound engine with default parameters
	soundengine = createIrrKlangDevice();

	if (!soundengine)
		return false;

	return true;
}

void Engine::Run()
{
	Init_GLUT::Run();
}

Engine::~Engine()
{
	if (scene_manager)
		delete scene_manager;
	soundengine->drop(); // delete engine
}