#ifndef __THATGAME_CORE_VERTEX_OBJECT_INCGRD__
#define __THATGAME_CORE_VERTEX_OBJECT_INCGRD__

#include "core/glad.h"

#include <optional>

namespace tg
{

template <int VertexDim = 3>
class VertexObject
{
            std::optional<unsigned int>   m_vao;
            std::optional<unsigned int>   m_vbo;

            size_t         m_num_vertices;

public:
                           VertexObject();
                           ~VertexObject();
                           VertexObject(const VertexObject&) = delete;
                           VertexObject(VertexObject&&) = delete;
                           VertexObject& operator=(const VertexObject&) = delete;
                           VertexObject& operator=(VertexObject&&) = delete;

            void           setVertices(float* m_vertices, size_t n);

            void           bind() const;

            void           draw() const;

};

} // namespace tg

#include "core/vertex_object.hpp"

#endif
