#include "Init_GLUT.h"
using namespace Core::Init;

extern Core::Init::Light Lighting;
extern Managers::Camera camera;
//make sure that static attributes are visible in cpp
Core::IListener *Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::Init(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo,
	const Core::FramebufferInfo& framebufferInfo)
{
	//EquilizeImage img2equilize("doctored_image");
	windowInformation = windowInfo;

	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version,
			contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		//As I said in part II, version doesn't matter
		// in Compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	//these functions were called in the old main.cpp
	//Now we use info from the structures
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x,
		windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: Initialized" << std::endl;
	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);


	// input functions
	glutKeyboardFunc(KeyboardGL);
	glutKeyboardUpFunc(KeyboardUpGL);
	glutSpecialFunc(SpecialGL);
	glutSpecialUpFunc(SpecialUpGL);
	glutMouseFunc(MouseGL);
	glutMotionFunc(MotionGL);

	//init GLEW, this can be called in main.cpp
	Init::Init_GLEW::Init();

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(windowInfo, contextInfo);
}

//starts the rendering Loop
void Init_GLUT::Run()
{
	std::cout << "GLUT:\tStart Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback()
{
	camera.g_CurrentTicks = std::clock();
	camera.deltaTicks = (float)(
		camera.g_CurrentTicks - camera.g_PreviousTicks
		);
	camera.g_PreviousTicks = camera.g_CurrentTicks;

	float fDeltaTime = 1 * camera.deltaTicks / (float)CLOCKS_PER_SEC;
	camera.cameraSpeed = 1.0f;
	if (camera.g_bShift)
	{
		camera.cameraSpeed = 5.0f;
	}
	camera.Translate(glm::vec3(camera.g_D - camera.g_A,
							camera.g_Q - camera.g_E,
							-camera.g_W + camera.g_S
							) * camera.cameraSpeed * fDeltaTime
					);

	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	if (listener) //check for NULL
	{
		listener->NotifyBeginFrame();
		listener->NotifyDisplayFrame();

		glutSwapBuffers();
		listener->NotifyEndFrame();
	}

}
void Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable == true)
	{
		if (listener)
		{
			listener->NotifyReshape(windowInformation.width, windowInformation.height);
		}
	}
}
//set the listener
void Init_GLUT::SetListener(Managers::Scene_Manager*& iListener)
{
	listener = iListener;
}
void Init_GLUT::closeCallback()
{
	close();
}
void Init_GLUT::enterFullScreen()
{
	glutFullScreen();
}
void Init_GLUT::extiFullScreen()
{
	glutLeaveFullScreen();
}
void Init_GLUT::SpecialGL(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		glutFullScreenToggle();
		windowInformation.Update_WindowSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case GLUT_KEY_SHIFT_L:
	case GLUT_KEY_SHIFT_R:
	{
		camera.g_bShift = true;
	}
		break;
	}
}
void Init_GLUT::SpecialUpGL(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_SHIFT_L:
	case GLUT_KEY_SHIFT_R:
	{
		camera.g_bShift = false;
	}
		break;
	}
}
void Init_GLUT::KeyboardGL(unsigned char c, int x, int y)
{
	float inc = 0.1f;
	switch (c)
	{
	case 'w':
	case 'W':
		camera.g_W = 1;
		break;
	case 'a':
	case 'A':
		camera.g_A = 1;
		break;
	case 's':
	case 'S':
		camera.g_S = 1;
		break;
	case 'd':
	case 'D':
		camera.g_D = 1;
		break;
	case 'q':
	case 'Q':
		camera.g_E = 1;
		break;
	case 'e':
	case 'E':
		camera.g_Q = 1;
		break;
	case 'r':
	case 'R':
		camera.SetPosition(camera.g_InitialCameraPosition);
		camera.SetRotation(camera.g_InitialCameraRotation);
		camera.g_Rotation = glm::quat();
		camera.g_Pitch = camera.g_Yaw = 0.0f;
		break;
	case 'I':
	case 'i':
		Lighting.gDiffuse.z -= inc;
		break;
	case 'K':
	case 'k':
		Lighting.gDiffuse.z += inc;
		break;
	case 'J':
	case 'j':
		Lighting.gDiffuse.x -= inc;
		break;
	case 'L':
	case 'l':
		Lighting.gDiffuse.x += inc;
		break;
	case 'O':
	case 'o':
		Lighting.gDiffuse.y -= inc;
		break;
	case 'U':
	case 'u':
		Lighting.gDiffuse.y += inc;
		break;
	case 'P':
	case 'p':
		Lighting.Reset();
		break;
	case ',':
		Lighting.setAmbeint(Lighting.gAmbient.x + inc/10.0f);
		break;
	case '.':
		Lighting.setAmbeint(Lighting.gAmbient.x - inc/10.0f);
		break;
	case 'M':
	case 'm':
		Lighting.setSpecularExp(-2);
		break;
	case 'n':
	case 'N':
		Lighting.setSpecularExp(2);
		break;
	case 'F':
	case 'f':
		Lighting.toggleflash();
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}
}
void Init_GLUT::KeyboardUpGL(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
	case 'W':
		camera.g_W = 0;
		break;
	case 'a':
	case 'A':
		camera.g_A = 0;
		break;
	case 's':
	case 'S':
		camera.g_S = 0;
		break;
	case 'd':
	case 'D':
		camera.g_D = 0;
		break;
	case 'q':
	case 'Q':
		camera.g_E = 0;
		break;
	case 'e':
	case 'E':
		camera.g_Q = 0;
		break;

	default:
		break;
	}
}
void Init_GLUT::MouseGL(int button, int state, int x, int y)
{
	camera.g_MousePos = glm::ivec2(x, y);
	camera.g_MouseButton = button;
	//Lighting.mouse_position = glm::vec3((float)x, (float)y, camera.GetPosition().z - 1.0f);
}
void Init_GLUT::MotionGL(int x, int y)
{
	glm::ivec2 mousePos = glm::ivec2(x, y);
	glm::vec2 delta = glm::vec2(camera.g_MousePos - mousePos);
	camera.g_MousePos = mousePos;

	glm::quat rotX = glm::angleAxis<float>(glm::radians(delta.y) * 0.5f, glm::vec3(1, 0, 0));
	glm::quat rotY = glm::angleAxis<float>(glm::radians(delta.x) * 0.5f, glm::vec3(0, 1, 0));

	//    camera.Rotate( rotX * rotY );

	if (camera.g_MouseButton == GLUT_LEFT_BUTTON)
	{
		camera.g_Pitch += delta.y * 0.5f;
		camera.g_Yaw += delta.x * 0.5f;

		camera.g_Pitch = glm::clamp(camera.g_Pitch, -80.0f, 80.0f);
		camera.g_Yaw = fmod(camera.g_Yaw, 360.0f);

		glm::quat cameraRotation = glm::toQuat(glm::eulerAngleYX(glm::radians(camera.g_Yaw), glm::radians(camera.g_Pitch)));
		camera.SetRotation(cameraRotation);
	}
	else
	{
		camera.g_Rotation = (rotY * rotX) * camera.g_Rotation; //x and y could be swapped to the original positions;
	}
}
void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo,
	const Core::ContextInfo& contextInfo)
{

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "************************" << std::endl;
}
Init_GLUT::Init_GLUT()
{
}
Init_GLUT::~Init_GLUT()
{
}