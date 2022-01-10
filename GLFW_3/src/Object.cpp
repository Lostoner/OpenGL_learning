#include "Object.h"
#include <iomanip>

void Object::PrintMat()
{
	glm::mat4 mat = glm::translate(ModelM, Position);
	std::cout << std::setw(12) << std::right << mat[0][0] << std::setw(12) << std::right << mat[0][1] << std::setw(12) << std::right << mat[0][2] << std::setw(12) << std::right << mat[0][3] << std::endl;
	std::cout << std::setw(12) << std::right << mat[1][0] << std::setw(12) << std::right << mat[1][1] << std::setw(12) << std::right << mat[1][2] << std::setw(12) << std::right << mat[1][3] << std::endl;
	std::cout << std::setw(12) << std::right << mat[2][0] << std::setw(12) << std::right << mat[2][1] << std::setw(12) << std::right << mat[2][2] << std::setw(12) << std::right << mat[2][3] << std::endl;
	std::cout << std::setw(12) << std::right << mat[3][0] << std::setw(12) << std::right << mat[3][1] << std::setw(12) << std::right << mat[3][2] << std::setw(12) << std::right << mat[3][3] << std::endl;
	std::cout << std::endl;
}

/*
Object::Object(void* vertexData, 
	unsigned int* indexData, 
	unsigned int vertexCount, 
	unsigned int indexCount, 
	std::string texPath,
	std::string uniformName,
	glm::vec3 position
) :
	va(VertexArray(true)),
	vb(VertexBuffer(vertexData, vertexCount)),
	ib(IndexBuffer(indexData, indexCount)),
	tex({ Texture(texPath) }),
	UniformName(uniformName)
{
	VertexCount = vertexCount;
	IndexCount = indexCount;

	Position = position;

	ModelM = glm::mat4(1.0f);

	Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	texNum = 0;
}
*/

Object::Object(void* vertexData,
	unsigned int* indexData,
	unsigned int vertexCount,
	unsigned int indexCount,
	std::string uniformName,
	glm::vec3 position
) :
	va(VertexArray(true)),
	vb(VertexBuffer(vertexData, vertexCount)),
	ib(IndexBuffer(indexData, indexCount)),
	UniformName(uniformName)
{
	VertexCount = vertexCount;
	IndexCount = indexCount;
	Position = position;
	ModelM = glm::mat4(1.0f);
	Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	texNum = 0;
}

Object::~Object()
{
	va.~VertexArray();
	vb.~VertexBuffer();
	ib.~IndexBuffer();
	/*
	if (tex.size() && tex[0].GetID())
	{
		for (int i = 0; i < tex.size(); i++)
		{
			tex[i].~Texture();
		}
	}
	*/
	for (int i = 0; i < texNum; i++)
	{
		free(texArray[i]);
		texArray[i] = nullptr;
	}
}

void Object::SetLayout(unsigned int type, unsigned int count)
{
	switch (type)
	{
		case UNSIGNED_INT:
			layout.push<unsigned int>(count);
			break;
		case FLOAT:
			layout.push<float>(count);
			break;
		case UNSIGNED_BYTE:
			layout.push<unsigned char>(count);
			break;
	}
}

void Object::SetTexture(unsigned int num, unsigned int unitNum)
{
	//if(num < tex.size() && tex[num].GetID())
	//	tex[num].Bind(unitNum);
	unitID = unitNum;
	if (texArray[num] != nullptr)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + unitNum));
		texArray[num]->Bind(unitNum);
	}
}

void Object::AddTexture(std::string texPath)
{
	//tex.push_back(Texture(texPath));
	ASSERT(texNum < 16);
	texArray[texNum] = new Texture(texPath);
	texNum++;
}

void Object::TexBind()
{
	for (int i = 0; i < texNum; i++)
	{
		texArray[i]->Bind(unitID);
	}
}

void Object::AttachBuffer()
{
	va.AddBuffer(vb, layout);
}

void Object::Bind()
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	/*
	if (tex.size())
	{
		for (int i = 0; i < tex.size(); i++)
		{
			tex[i].Bind();
		}
	}
	*/
}

void Object::Unbind()
{
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	//for (int i = 0; i < texNum; i++)
	//{
	//	texArray[i]->Unbind();
	//}
}

void Object::SetUniform(Shader& shader, std::string uniform)
{
	glm::mat4 TMatrix = ModelM;
	TMatrix[3][0] = Position[0];
	TMatrix[3][1] = Position[1];
	TMatrix[3][2] = Position[2];
	shader.setUniformMatrix4fv(uniform, TMatrix);
}

void Object::Translate(const float x, const float y, const float z)
{
	Position += glm::vec3(x, y, z);
	//std::cout << Position[0] << ", " << Position[1] << ", " << Position[2] << std::endl;
}

void Object::Move(const float x, const float y, const float z)
{
	SetPosition(x, y, z);
}

void Object::Scale(const float ratex, const float ratey, const float ratez)
{
	ModelM = glm::scale(ModelM, glm::vec3(ratex, ratey, ratez));
}

void Object::Rotate(const float theta, const glm::vec3& axis)
{
	ModelM = glm::rotate(ModelM, glm::radians(theta), axis); 
}

glm::mat4 Object::GetMatrix()
{
	glm::mat4 TMatrix = ModelM;
	TMatrix[3][0] = Position[0];
	TMatrix[3][1] = Position[1];
	TMatrix[3][2] = Position[2];
	return TMatrix;
}

void Object::SetColor(glm::vec4 newColor)
{
	Color = newColor;
}

void Object::PlusColor(glm::vec4 newColor)
{
	Color += newColor;
}