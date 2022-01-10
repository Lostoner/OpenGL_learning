#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Shader::Shader(const std::vector<std::string>& filePathes, int i1, int i2) :
    m_filePath(filePathes), m_rendererID(0)
{
    std::vector<std::vector<std::string>> sourceCodes;
    for (unsigned int i = 0; i < filePathes.size(); i++)
    {
        sourceCodes.push_back(readingShader(filePathes[i]));
    }
    shaderStruct specificShaders({ sourceCodes[0][i1], sourceCodes[1][i2] });
    //std::cout << "vertex shader: " << sourceCodes[0][i1] << std::endl;
    //std::cout << "fragment shader: " << sourceCodes[1][i2] << std::endl;

    m_rendererID = createShader(specificShaders);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

std::vector<std::string> Shader::readingShader(const std::string& shaderPath)
{
    std::ifstream shaderStream(shaderPath);
    std::vector<std::string> shaders;
    bool flag = 0;

    std::string line;
    std::string temStr = "";
    while (getline(shaderStream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            flag = 1;
        }
        else if (line.find("#end") != std::string::npos)
        {
            flag = 0;
            shaders.push_back(temStr);
            temStr = "";
        }
        else if (flag)
        {
            temStr += line;
            temStr += '\n';
        }
    }
    return shaders;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Compiling shader " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << " failed!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const shaderStruct allShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, allShader.vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, allShader.fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

//Set Uniform
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int v0)
{
    GLCall(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& mat)
{
    /*
    std::cout << "[Matrix]: " << std::endl;
    std::cout << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << std::endl;
    std::cout << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << std::endl;
    std::cout << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << std::endl;
    std::cout << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << std::endl;
    */

    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform1f(const std::string& name, float v0)
{
    GLCall(glUniform1f(getUniformLocation(name), v0));
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    {
        return (m_uniformLocationCache[name]);
    }
    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1)
    {
        std::cout << "Uniform " << location << " doesn't exist." << std::endl;
    }
    m_uniformLocationCache[name] = location;
    return location;
}