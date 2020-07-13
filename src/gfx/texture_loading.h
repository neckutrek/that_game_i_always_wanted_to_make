#ifndef __THATGAME_CORE_TEXTURE_LOADING_INCGRD__
#define __THATGAME_CORE_TEXTURE_LOADING_INCGRD__

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "gfx/stb_image.h"

#include <string>

namespace tg
{

unsigned int loadTexture(const std::string& filepath)
{
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true);
   unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
   if (!data)
   {
      throw Exception("Failed to load texture.");
   }

   unsigned int textureId = 0;
   glGenTextures(1, &textureId);
   glBindTexture(GL_TEXTURE_2D, textureId);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);

   glBindTexture(GL_TEXTURE_2D, 0);

   stbi_image_free(data);

   return textureId;
}


} // namespace tg

#endif
