#include "Texture.h"
#include <iostream>
#include <string>
#include "vender/stb_image/stb_image.h"


Texture::Texture() :
	m_rendererID(0),
	m_localBuffer(nullptr),
	width(0),
	height(0),
	bytepp(0)
{}

Texture::Texture(const std::string& filePath) :
	m_rendererID(0), 
	m_filePath(filePath), 
	m_localBuffer(nullptr), 
	width(0), 
	height(0), 
	bytepp(0)
{
	//std::cout << "Texture constructed" << std::endl;
	if (m_filePath == "")
	{
		return;
	}
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(m_filePath.c_str(), &width, &height, &bytepp, 4);

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer)
	{
		stbi_image_free(m_localBuffer);
	}
}

Texture::~Texture()
{
	std::cout << "delete" << std::endl;
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}