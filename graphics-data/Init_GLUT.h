#pragma once
#include "ContextInfo.h"
#include "FramebufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"
#include "IListener.h"
#include "Scene_Manager.h"
//#include "EqulizeImage.h"

namespace Core
{
	namespace Init
	{
		class Init_GLUT
		{
		public:

			static void SetListener(Managers::Scene_Manager*& iListener);

			static void Init(const Core::WindowInfo &window,
							const Core::ContextInfo &context,
							const Core::FramebufferInfo &framebufferInfo);

			static void Run();
			static void close();

			void enterFullScreen();
			void extiFullScreen();

			static void printOpenGLInfo(const Core::WindowInfo &windowInfo,
										const Core::ContextInfo &context);

			Init_GLUT();
			~Init_GLUT();
		private:

			static Core::IListener* listener;
			static Core::WindowInfo windowInformation;
			static void idleCallback(void);
			static void displayCallback(void);
			static void reshapeCallback(int width, int height);
			static void SpecialGL(int key, int x, int y);
			static void SpecialUpGL(int key, int x, int y);
			static void KeyboardGL(unsigned char c, int x, int y);
			static void KeyboardUpGL(unsigned char c, int x, int y);
			static void MouseGL(int button, int state, int x, int y);
			static void MotionGL(int x, int y);
			static void PassiveMotionGL(int x, int y);
			static void closeCallback();
		};
	};

};