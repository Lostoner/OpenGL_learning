#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <iostream>

VertexArray::VertexArray() :
	m_RendererID(0)
{

}

VertexArray::VertexArray(bool flag)
{
	if (flag)
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
	}
	else
	{
		m_RendererID = 0;
	}
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, 
			element.count,
			element.type,
			element.normalized,
			layout.getStride(),
			(const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);

	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}