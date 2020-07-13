#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include "core/shader_types.h"
#include "core/exception.h"

namespace tg
{

template <typename ...Shaders>
ShaderProgram
ShaderBuilder::linkShaderProgram(
   const Shader& shader,
   const Shaders&... shaders)
{
   ShaderProgram program;
   program.m_handle = glCreateProgram();

   auto attachShader = [&program](const Shader& shader){
      glAttachShader(program.m_handle, shader.m_handle);
   };

   attachShader(shader);
   (attachShader(shaders), ...);

   glLinkProgram(program.m_handle);

   int  success;
   char infoLog[512];
   glGetProgramiv(program.m_handle, GL_LINK_STATUS, &success);
   if(!success) {
      glGetProgramInfoLog(program.m_handle, 512, NULL, infoLog);
      throw Exception("Error when linking shader program: " + std::string(infoLog));
   }

   return program;
}

template <typename ...Shaders>
void
ShaderBuilder::deleteShaders(
   const Shader& shader,
   const Shaders&... shaders)
{
   auto deleteShader = [](const Shader& shader){
      glDeleteShader(shader.m_handle);
   };

   deleteShader(shader);
   (deleteShader(shaders), ...);
}

} // namespace tg
