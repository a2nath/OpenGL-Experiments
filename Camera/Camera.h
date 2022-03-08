/**
 * Basic camera class.
 */
#pragma once
#include <fstream>
#include <GL/glew.h>
#include <GL/wglew.h> // For wglSwapInterval
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <ctime>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800

#define START_POSITION_X 400
#define START_POSITION_Y 0

#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

//int g_iWindowWidth = 800;
//int g_iWindowHeight = 600;
namespace Managers{

	class Camera
	{
	public:

		Camera();
		Camera(int screenWidth, int screenHeight);

		void SetViewport(int x, int y, int width, int height);
		glm::vec4 GetViewport() const;

		void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

		void ApplyViewMatrix();

		void SetPosition(const glm::vec3& pos, GLboolean set_initial = 0);
		glm::vec3 GetPosition() const;

		// Translate the camera by some amount. If local is TRUE (default) then the translation should
		// be applied in the local-space of the camera. If local is FALSE, then the translation is
		// applied in world-space.
		void Translate(const glm::vec3& delta, bool local = true);

		void SetRotation(const glm::quat& rot);
		glm::quat GetRotation() const;

		void SetEulerAngles(const glm::vec3& eulerAngles);
		glm::vec3 GetEulerAngles() const;

		// Rotate the camera by some amount.
		void Rotate(const glm::quat& rot);

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();


		// Model, View, Projection matrix uniform variable in shader program.
		GLint g_uniformMVP = -1;

		int g_iWindowHandle = 0;
		int g_W, g_A, g_S, g_D, g_Q, g_E;
		bool g_bShift = false;

		glm::vec3 g_InitialCameraPosition;
		glm::quat g_InitialCameraRotation;
		glm::ivec2 g_MousePos;
		int g_MouseButton;
		glm::quat g_Rotation;

		std::clock_t g_PreviousTicks;
		std::clock_t g_CurrentTicks;
		float g_Pitch = 0.0f;
		float g_Yaw = 0.0f;

		struct VertexXYZColor
		{
			glm::vec3 m_Pos;
			glm::vec3 m_Color;
		};

		float cameraSpeed, deltaTicks;
	protected:

		void UpdateViewMatrix();

		glm::vec4 m_Viewport;

		glm::vec3 m_Position;
		glm::quat m_Rotation;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

	private:
		bool m_ViewDirty;
	};
}
extern Managers::Camera camera;
