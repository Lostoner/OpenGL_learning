#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#define UNSIGNED_INT 0
#define FLOAT 1
#define UNSIGNED_BYTE 2

class Object
{
private:
	unsigned int VertexCount;
	unsigned int IndexCount;

	glm::vec3 Position;
	glm::mat4 ModelM;

	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
	IndexBuffer ib;
	Texture* texArray[16];
	int texNum;
	int unitID;

	std::string UniformName;

	glm::vec4 Color;

public:
	/*
	Object(void* vertexData, 
		unsigned int* indexData, 
		unsigned int vertexCount, 
		unsigned int indexCount, 
		std::string texPath, 
		std::string uniformName, 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
	);
	*/
	Object(void* vertexData,
		unsigned int* indexData,
		unsigned int vertexCount,
		unsigned int indexCount,
		std::string uniformName,
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
	);
	~Object();
	void SetLayout(unsigned int type, unsigned int count);
	void SetTexture(unsigned int num = 0, unsigned int unitNum = 0);
	void AddTexture(std::string texPath);
	void TexBind();
	void AttachBuffer();
	void Bind();
	void Unbind();

	void SetUniform(Shader& shader, std::string uniform);
	void Translate(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void Move(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	void Scale(const float ratex = 1.0f, const float ratey = 1.0f, const float ratez = 1.0f);
	void Rotate(const float theta = 0.0f, const glm::vec3& axis = glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 GetPosition() { return Position; }
	void SetPosition(const float x, const float y, const float z) { Position[0] = x; Position[1] = y; Position[2] = z; }
	VertexArray* GetVA() { return &va; }
	IndexBuffer* GetIB() { return &ib; }
	unsigned int GetIBCount() { return ib.getCount(); }
	glm::mat4 GetMatrix();

	void PrintMat();

	void SetColor(glm::vec4 newColor);
	void PlusColor(glm::vec4 newColor);
};