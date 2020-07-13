#include "core/glad.h"
#include "core/vertex_object.h"

namespace tg
{

template <int VertexDim>
VertexObject<VertexDim>::VertexObject()
: m_vao(std::nullopt), m_vbo(std::nullopt)
{}

template <int VertexDim>
VertexObject<VertexDim>::~VertexObject()
{
   if (m_vao)
   {
      glDeleteVertexArrays(1, &m_vao.value());
   }
   if (m_vbo)
   {
      glDeleteBuffers(1, &m_vbo.value());
   }
}

template <int VertexDim>
void VertexObject<VertexDim>::setVertices(
   float* m_vertices,
   size_t n)
{
   unsigned int vao = 0;
   unsigned int vbo = 0;
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glBindVertexArray(vao);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n * VertexDim, m_vertices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, VertexDim, GL_FLOAT, GL_FALSE, VertexDim * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   m_vao = std::make_optional<unsigned int>(vao);
   m_vbo = std::make_optional<unsigned int>(vbo);
   m_num_vertices = n;
}

template <int VertexDim>
void VertexObject<VertexDim>::bind() const
{
   if (m_vao)
   {
      glBindVertexArray(m_vao.value());
   }
}

template <int VertexDim>
void VertexObject<VertexDim>::draw() const
{
   glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
}

} // namespace tg
