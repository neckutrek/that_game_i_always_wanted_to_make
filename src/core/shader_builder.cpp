#include "core/shader_builder.h"
#include "core/shader_types.h"
#include "core/exception.h"

#include <fstream>

namespace tg
{

Shader
ShaderBuilder::buildShader(
   const std::string& sourceFilename,
   GLenum shaderType)
{
   std::string::size_type st = sourceFilename.find_last_of('.');
   if (st == std::string::npos)
   {
      throw Exception(
         "Can't open GLSL source file: '" + sourceFilename + "'. "
         "The given filename has no extension.");
   }

   if (sourceFilename.substr(st).compare(".glsl") != 0)
   {
      throw Exception(
         "Can't open GLSL source file: '" + sourceFilename + "'. "
         "The file extension is not '.glsl'.");
   }

   std::ifstream ifs(sourceFilename);
   if (!ifs)
   {
      throw Exception(
         "Can't open GLSL source file: '" + sourceFilename + "'. ");
   }

   std::string shaderSource = "";
   ifs.seekg(0, std::ios::end);
   shaderSource.reserve(ifs.tellg());
   ifs.seekg(0, std::ios::beg);
   shaderSource.assign(
      (std::istreambuf_iterator<char>(ifs)),
      std::istreambuf_iterator<char>());

   Shader shader;
   shader.m_shaderType = shaderType;
   shader.m_handle = glCreateShader(shader.m_shaderType);
   const char* sourceString = shaderSource.c_str();
   glShaderSource(shader.m_handle, 1, &sourceString, NULL);
   glCompileShader(shader.m_handle);

   int  success;
   char infoLog[512];
   glGetShaderiv(shader.m_handle, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(shader.m_handle, 512, NULL, infoLog);
      throw Exception("Error when compiling shader: " + std::string(infoLog));
   }

   return shader;
}

} // namespace tg
