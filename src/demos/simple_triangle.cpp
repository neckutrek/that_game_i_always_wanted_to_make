#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#include "gfx/shader_types.h"
#include "gfx/shader_builder.h"
#include "gfx/vertex_object.h"

#include <iostream>

using namespace tg;

static constexpr int SCREEN_WIDTH = 1024;
static constexpr int SCREEN_HEIGHT = 768;

auto createSdlWindow()
{
   SDL_Init( SDL_INIT_VIDEO );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

   SDL_Window* window = SDL_CreateWindow(
      "Simple Triangle",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

   SDL_GLContext context = SDL_GL_CreateContext( window );

   return std::make_tuple(window, context);
}

int main()
{
   auto [window, context] = createSdlWindow();
   if (!window)
   {
      return -1;
   }

   Shader vertexShader = ShaderBuilder::buildShader("../src/shaders/vertex.vert");
   Shader fragmentShader = ShaderBuilder::buildShader("../src/shaders/fragment.frag");
   ShaderProgram shaderProgram = ShaderBuilder::linkShaderProgram(vertexShader, fragmentShader);
   ShaderBuilder::deleteShaders(vertexShader, fragmentShader);
   glUseProgram(shaderProgram.m_handle);

   float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
   };

   VertexObject triangle;
   triangle.set(vertices, 3);
   triangle.bind();

   bool run = true;
   while(run)
   {
      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         switch( event.type )
         {
         case SDL_KEYUP:
            if( event.key.keysym.sym == SDLK_ESCAPE )
               run = false;
            break;
         }
      }

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      triangle.draw();

      SDL_GL_SwapWindow( window );
      SDL_Delay( 1 );
   }

   glDeleteProgram(shaderProgram.m_handle);

   SDL_GL_DeleteContext( context );
   SDL_DestroyWindow( window );
   SDL_Quit();

   return 0;
}