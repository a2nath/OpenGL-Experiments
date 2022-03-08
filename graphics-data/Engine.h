#pragma once
#include "Init_GLUT.h"
#include "Scene_Manager.h"

class Engine
{
public:
	Engine();
	~Engine();
	void Run();
	bool Init();
private:
	Managers::Scene_Manager* scene_manager;
};

