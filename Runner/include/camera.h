
#pragma once

#if !defined(_CAMERA_H_)
#define _CAMERA_H_
// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

//#define YAW -90.0f
//#define PITCH 0.0f
//#define SPEED 3.0f
//#define SENSITIVTY 0.25f
//#define ZOOM 45.0f
// Default camera values
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = -20.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.25f;
	const GLfloat ZOOM = 45.0f;

	const GLuint WIDTH = 800, HEIGHT = 600;
// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	static Camera camera;
	static glm::mat4 view;
	static glm::mat4 projection;
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	GLfloat deltaTime = 0.0f;

	glm::vec3 directVec;

	bool flag;

	//Camera();
	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	// Constructor with scalar values
	//Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	void init(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();


	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);


	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset);

	void setPosition(glm::vec3 playerPos);

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};

#endif
