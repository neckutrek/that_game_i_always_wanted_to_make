#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

namespace tg
{

template <int VertexDim1, int... VertexDims>
VertexObject<VertexDim1, VertexDims...>::VertexObject()
: m_vao(std::nullopt), m_vbo(std::nullopt), m_ebo(std::nullopt),
  m_num_vertices(0), m_num_elements(0)
{}

template <int VertexDim1, int... VertexDims>
VertexObject<VertexDim1, VertexDims...>::~VertexObject()
{
   destroyBuffers();
}

template <int VertexDim1, int... VertexDims>
void VertexObject<VertexDim1, VertexDims...>::set(
   float* vertices,
   size_t n,
   unsigned int* elements,
   size_t m)
{
   destroyBuffers();

   unsigned int vao = 0;
   unsigned int vbo = 0;
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glBindVertexArray(vao);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);

   unsigned int ebo = 0;
   if (elements)
   {
      glGenBuffers(1, &ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m * 3, elements, GL_STATIC_DRAW);
   }

   unsigned int i = 0;
   unsigned int offset = 0;
   auto setAttributes = [&i, &offset](int dim){
      glVertexAttribPointer(
         i, dim, GL_FLOAT, GL_FALSE,
         m_vertex_size * sizeof(float),
         (void*)(offset * sizeof(float)));
      glEnableVertexAttribArray(i);
      ++i;
      offset += dim;
   };
   setAttributes(VertexDim1);
   (setAttributes(VertexDims), ...);

   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n * offset, vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   m_vao = std::make_optional<unsigned int>(vao);
   m_vbo = std::make_optional<unsigned int>(vbo);
   if (elements)
   {
      m_ebo = std::make_optional<unsigned int>(ebo);
   }
   m_num_vertices = n;
   m_num_elements = m * 3;
}

template <int VertexDim1, int... VertexDims>
void VertexObject<VertexDim1, VertexDims...>::bind() const
{
   if (m_vao)
   {
      glBindVertexArray(m_vao.value());
   }
}

template <int VertexDim1, int... VertexDims>
void VertexObject<VertexDim1, VertexDims...>::destroyBuffers()
{
   if (m_vao)
   {
      glDeleteVertexArrays(1, &m_vao.value());
   }
   if (m_vbo)
   {
      glDeleteBuffers(1, &m_vbo.value());
   }
   if (m_ebo)
   {
      glDeleteBuffers(1, &m_ebo.value());
   }
}

template <int VertexDim1, int... VertexDims>
void VertexObject<VertexDim1, VertexDims...>::draw() const
{
   if (!m_vao || !m_vbo)
   {
      return;
   }
   if (m_ebo)
   {
      glDrawElements(GL_TRIANGLES, m_num_elements, GL_UNSIGNED_INT, 0);
   }
   else
   {
      glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
   }
}

} // namespace tg
