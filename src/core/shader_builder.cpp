#include "core/shader_builder.h"
#include "core/shader_types.h"
#include "core/exception.h"

#include <fstream>

namespace tg
{

Shader
ShaderBuilder::buildShader(
   const std::string& sourceFilename)
{
   std::string::size_type st = sourceFilename.find_last_of('.');
   if (st == std::string::npos)
   {
      throw Exception(
         "Can't open GLSL source file: '" + sourceFilename + "'. "
         "The given filename has no extension.");
   }

   std::string extension = sourceFilename.substr(st);
   bool is_vertex = (extension.compare(".vert") == 0);
   bool is_fragment = (extension.compare(".frag") == 0);
   bool is_geometry = (extension.compare(".geom") == 0);
   if (!is_vertex && !is_fragment && !is_geometry)
   {
      throw Exception(
         "Can't open GLSL source file: '" + sourceFilename + "'. "
         "The file extension is not one of '.vert', '.frag' or '.geom'.");
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

   shader.m_shaderType = 0;
   if (is_vertex) shader.m_shaderType = GL_VERTEX_SHADER;
   if (is_fragment) shader.m_shaderType = GL_FRAGMENT_SHADER;
   if (is_geometry) shader.m_shaderType = GL_GEOMETRY_SHADER;

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
