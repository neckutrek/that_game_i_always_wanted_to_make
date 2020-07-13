#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#include "core/shader_types.h"
#include "core/shader_builder.h"
#include "core/vertex_object.h"
#include "core/texture_loading.h"
#include "core/object3d.h"

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

   glEnable(GL_DEPTH_TEST);

   return std::make_tuple(window, context);
}

int main()
{
   auto [window, context] = createSdlWindow();
   if (!window)
   {
      return -1;
   }

   Shader vertexShader = ShaderBuilder::buildShader("../src/shaders/pos_col_tex.vert");
   Shader fragmentShader = ShaderBuilder::buildShader("../src/shaders/tex.frag");
   ShaderProgram shaderProgram = ShaderBuilder::linkShaderProgram(vertexShader, fragmentShader);
   ShaderBuilder::deleteShaders(vertexShader, fragmentShader);
   glUseProgram(shaderProgram.m_handle);
   glUniform1i(glGetUniformLocation(shaderProgram.m_handle, "ourTexture"), 0);

   unsigned int texture1 = loadTexture("../assets/container.jpg");
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture1);

   float vertices[] = {
      // positions          // colors           // texture coords
      // lid 1
       0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

      // lid2
       0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

      // etc.
      -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

       0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

       0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

       0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
   };

   unsigned int indices[] = {
   // triangle 1        triangle 2
       0,  1,  3,        1,  2,  3, // lid 1
       4,  5,  7,        5,  6,  7, // lid 2
       8,  9, 11,        9, 10, 11, // etc.
      12, 13, 15,       13, 14, 15,
      16, 17, 19,       17, 18, 19,
      20, 21, 23,       21, 22, 23
   };

   VertexObject<3,3,2> boxModel1;
   boxModel1.set(vertices, 4*6, indices, 2*6);

   glm::mat4 projection = glm::mat4(1.0f);
   projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
   glUniformMatrix4fv(
      glGetUniformLocation(shaderProgram.m_handle, "projection"),
      1, GL_FALSE, &projection[0][0]);

   Object3D cameraObject;
   cameraObject.translate( {0.0f, 0.0f, -3.0f} );
   glUniformMatrix4fv(
      glGetUniformLocation(shaderProgram.m_handle, "view"),
      1, GL_FALSE, cameraObject.mtx00());

   glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

   Object3D boxObject;
   float rotSpeed = 0.10f;
   glm::vec3 rotAxis = {1.0f, 1.0f, 1.0f};

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
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (const auto& pos : cubePositions)
      {
         boxObject.setPosition(pos);
         boxObject.rotate(glm::radians(rotSpeed), rotAxis);
         glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram.m_handle, "model"),
            1, GL_FALSE, boxObject.mtx00());

         boxModel1.bind();
         boxModel1.draw();
      }

      SDL_GL_SwapWindow( window );
      SDL_Delay( 1 );
   }

   glDeleteTextures(1, &texture1);
   glDeleteProgram(shaderProgram.m_handle);

   SDL_GL_DeleteContext( context );
   SDL_DestroyWindow( window );
   SDL_Quit();
   
   return 0;
}