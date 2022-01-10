#include <iostream>
#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* fileName, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << ")" <<
            " " << "occurs in function: " << functionName << std::endl <<
            "[File]: " << fileName << std::endl <<
            "[Line]: " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shaders) const
{
    shaders.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

/*
void Renderer::Draw(Object& obj, const Shader& shaders) const
{
    obj.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, obj.GetIBCount(), GL_UNSIGNED_INT, nullptr));
}
*/

void Renderer::DrawLine(const VertexArray& va, const IndexBuffer& ib, const Shader& shaders) const
{
    shaders.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_LINE, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}