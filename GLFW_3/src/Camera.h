#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#define DelUD 0
#define DelLR 1

#define Forward 0
#define Backward 1
#define Leftward 2
#define Rightward 3
#define Upward 4
#define Downward 5

class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 Face;
	glm::vec3 Top;
	glm::vec3 Right;
	glm::mat4 ViewM;
	std::string UniformName;

	float Yaw;
	float Pitch;

	float Dpi;
	float Speed;
	float LastFrame;

public:
	Camera(std::string uniformName, 
		int height, 
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 fac = glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3 top = glm::vec3(0.0f, 1.0f, 0.0f)
		);
	~Camera();

	void MovePosition(int Type);
	void SetPosition(glm::vec3 tar);

	void ChangeFace(float horizontal = 0, float vertical = 0);
	void AimDel();

	glm::vec3 GetPosition() { return Position; }
	glm::vec3 GetFace() { return Face; }
	glm::vec3 GetTop() { return Top; }
	glm::mat4 GetMatrix() { return glm::lookAt(Position, Position + Face, Top); }

	void ListeningKey(GLFWwindow* window);

	void PrintFace();
};