#ifndef __THATGAME_CORE_VERTEX_OBJECT_INCGRD__
#define __THATGAME_CORE_VERTEX_OBJECT_INCGRD__

#include <optional>

namespace tg
{

template <int VertexDim1 = 3, int... VertexDims>
class VertexObject
{
            std::optional<unsigned int>   m_vao;
            std::optional<unsigned int>   m_vbo;
            std::optional<unsigned int>   m_ebo;

            size_t         m_num_vertices;
            size_t         m_num_elements;

   static constexpr size_t m_vertex_size = (VertexDim1 + ... + VertexDims);

public:
                           VertexObject();

                           ~VertexObject();

                           VertexObject(const VertexObject&) = delete;
                           VertexObject(VertexObject&&) = delete;
                           VertexObject& operator=(const VertexObject&) = delete;
                           VertexObject& operator=(VertexObject&&) = delete;

   ///
   /// @param m should be the number of elements in the @elements array DIVIDED BY 3!
   ///
            void           set(
                              float* vertices,
                              size_t n,
                              unsigned int* elements = nullptr,
                              size_t m = 0);

            void           bind() const;

            void           draw() const;

private:
            void           destroyBuffers();
};

} // namespace tg

#include "gfx/vertex_object.hpp"

#endif
