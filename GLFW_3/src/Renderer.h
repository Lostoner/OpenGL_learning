#pragma once
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* functionName, const char* fileName, int line);

class Renderer
{
private:

public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaders) const;
    //void Draw(Object& obj, const Shader& shaders) const;
    void DrawLine(const VertexArray& va, const IndexBuffer& ib, const Shader& shaders) const;
    void Clear() const;
};