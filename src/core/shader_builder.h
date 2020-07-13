#ifndef __THATGAME_CORE_SHADER_BUILDER_INCGRD__
#define __THATGAME_CORE_SHADER_BUILDER_INCGRD__

#include <string>

namespace tg
{

struct Shader;
struct ShaderProgram;

/***
 *    Responsibilities:
 *       - Builds shaders
 *       - Links shader programs
 *       - Deletes shaders
 */
class ShaderBuilder
{
public:
                           ShaderBuilder() = default;
                           ~ShaderBuilder() = default;

                           ShaderBuilder(
                              const ShaderBuilder&) = delete;

                           ShaderBuilder(
                              ShaderBuilder&&) = delete;

            ShaderBuilder& operator=(
                              const ShaderBuilder&) = delete;
            ShaderBuilder& operator=(
                              ShaderBuilder&&) = delete;

   static   Shader         buildShader(
                              const std::string& sourceFilename);

   template <typename ...Shaders>
   static   ShaderProgram  linkShaderProgram(
                              const Shader& shader,
                              const Shaders&... shaders);

   template <typename ...Shaders>
   static   void           deleteShaders(
                              const Shader& shader,
                              const Shaders&... shaders);

};

} // namespace tg

#include "core/shader_builder.hpp"

#endif
