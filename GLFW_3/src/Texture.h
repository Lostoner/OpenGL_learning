#pragma once
#include "Renderer.h"

class Texture
{
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int width, height, bytepp;

public:
	Texture();
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
	inline unsigned int GetID() const { return m_rendererID; }
};