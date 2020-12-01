#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));   // generating a buffer and giving back an id.
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));  // selecting that buffer.
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // specify how large the data is going to be.
    // example - glBufferData(GL_ARRAY_BUFFER, size of (float) * 6, positions[] , GL_STATIC_DRAW)
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));  // selecting that buffer.
}
