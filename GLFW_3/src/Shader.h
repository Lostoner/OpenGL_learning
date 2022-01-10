#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct shaderStruct {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	std::vector<std::string> m_filePath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	Shader(const std::vector<std::string>& filePath, int i1, int i2);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniform
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int v0);
	void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform1f(const std::string& name, float v0);

private:
	std::vector<std::string> readingShader(const std::string& shaderPath);
	static unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const shaderStruct allShader);
	int getUniformLocation(const std::string& name);
};