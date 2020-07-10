#ifndef __THATGAME_CORE_SHADER_TYPES_INCGRD__
#define __THATGAME_CORE_SHADER_TYPES_INCGRD__

#include "core/glad.h"

namespace tg
{

struct Shader
{
            unsigned int   m_handle = 0;
            GLenum         m_shaderType = 0;
};

struct ShaderProgram
{
            unsigned int   m_handle = 0;
};

} // namespace tg

#endif
