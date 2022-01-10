#include "Camera.h"
#include <iostream>
#include <iomanip>

Camera::Camera(std::string uniformName, 
	int height, 
	glm::vec3 pos, 
	glm::vec3 fac, 
	glm::vec3 top) :
	UniformName(uniformName),
	Position(pos),
	Face(fac),
	Top(top)
{
	Yaw = -90;
	Pitch = 0;

	Right = glm::cross(Face, Top);
	Dpi = (float)60 / (float)height;
	Speed = 0.05;
	LastFrame = glfwGetTime();
}

Camera::~Camera()
{
}

void Camera::MovePosition(int Type)
{
	switch (Type)
	{
	case Forward:
		Position += Face * Speed;
		break;
	case Backward:
		Position -= Face * Speed;
		break;
	case Leftward:
		Position -= Right * Speed;
		break;
	case Rightward:
		Position += Right * Speed;
		break;
	case Upward:
		Position += glm::vec3(0.0f, 1.0f, 0.0f) * Speed;
		break;
	case Downward:
		Position -= glm::vec3(0.0f, 1.0f, 0.0f) * Speed;
	}
}

void Camera::SetPosition(glm::vec3 tar)
{
	Position = tar;
}

void Camera::ChangeFace(float horizontal, float vertical)
{
	float curTime = glfwGetTime();
	float delTime = curTime - LastFrame;
	LastFrame = curTime;

	Pitch += vertical * Dpi;
	if (Pitch >= 90.0)
	{
		Pitch = 89.99;
	}
	else if (Pitch <= -90.0)
	{
		Pitch = -89.99;
	}

	Yaw += horizontal * Dpi;
	AimDel();
}

void Camera::AimDel()
{
	Face[0] = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Face[1] = sin(glm::radians(Pitch));
	Face[2] = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

	Face = glm::normalize(Face);
	Right = glm::normalize(glm::cross(Face, glm::vec3(0.0f, 1.0f, 0.0f)));
	Top = glm::normalize(glm::cross(Right, Face));
}

void Camera::ListeningKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		MovePosition(Forward);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		MovePosition(Backward);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		MovePosition(Leftward);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		MovePosition(Rightward);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		MovePosition(Upward);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		MovePosition(Downward);
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Camera::PrintFace()
{
	std::cout << std::setw(12) << std::right << Face[0] << std::setw(12) << std::right << Face[1] << std::setw(12) << std::right << Face[2] << std::endl;
}