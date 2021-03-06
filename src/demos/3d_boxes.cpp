#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#include "core/clock.h"
#include "core/object3d.h"
#include "core/camera.h"
#include "core/utilities.h"

#include "gfx/shader_types.h"
#include "gfx/shader_builder.h"
#include "gfx/vertex_object.h"
#include "gfx/texture_loading.h"

#include "glm/ext/matrix_clip_space.hpp"

#include <iostream>

using namespace tg;

static constexpr int SCREEN_WIDTH = 1280;
static constexpr int SCREEN_HEIGHT = 800;
static constexpr int FPS = 30;

static const ClockTime FRAME_DURATION = Clock::ms(1'000/FPS);

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
      //SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      0, 0,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

   SDL_GLContext context = SDL_GL_CreateContext( window );

   glEnable(GL_DEPTH_TEST);

   SDL_SetRelativeMouseMode(SDL_TRUE);

   return std::make_tuple(window, context);
}

int main()
{
   auto [window, context] = createSdlWindow();
   if (!window)
   {
      return -1;
   }

   Clock::now(); // Set the in-game clock to start now

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

   std::vector<glm::vec3> cubePositions;
   for (const auto& pos : {
         //glm::vec3( 0.0f,  0.0f,  0.0f),
         glm::vec3( 2.0f,  5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3( 2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f,  3.0f, -7.5f),
         glm::vec3( 1.3f, -2.0f, -2.5f),
         glm::vec3( 1.5f,  2.0f, -2.5f),
         glm::vec3( 1.5f,  0.2f, -1.5f),
         glm::vec3(-1.3f,  1.0f, -1.5f)
      })
   {
      cubePositions.push_back(pos);
   }

   {
      int w = 11;
      int h = 11;
      for (int i = 0; i<w; ++i)
         for (int j=0; j<h; ++j)
            cubePositions.push_back( glm::vec3( float(i)-float(w)/2.0f,  -1.1f, float(j)-float(h)/2.0f) );
   }

   Object3D boxObject;
   float rotSpeed = M_PI/4; // [rad/sec]
   glm::vec3 rotAxis = {1.0f, 1.0f, 1.0f};

   Camera cameraObject;
   cameraObject.translate( {0.0f, 0.0f, -3.0f} );
   float cameraSpeed = M_PI/4; // [rad/sec]

   bool warpMouse = true;
   const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
   ClockTime last_tick = Clock::now();
   bool run = true;
   while(run)
   {
      int mouseSpeedX = 0;
      int mouseSpeedY = 0;

      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         switch( event.type )
         {
         case SDL_KEYUP:
            if( event.key.keysym.sym == SDLK_ESCAPE )
               run = false;
            break;
         case SDL_QUIT:
            run = false;
            break;
         case SDL_MOUSEMOTION:
            mouseSpeedX += event.motion.xrel;
            mouseSpeedY += event.motion.yrel;
            break;
         }
      }

      if (warpMouse)
      {
         SDL_SetRelativeMouseMode(SDL_TRUE);
         SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
      }
      else
      {
         SDL_SetRelativeMouseMode(SDL_FALSE);
      }

      float cameraSpeedPerFrame = cameraSpeed * Clock::sec(FRAME_DURATION);

      if (keyboard_state[SDL_SCANCODE_N]) {
         warpMouse = true;
      }
      if (keyboard_state[SDL_SCANCODE_M]) {
         warpMouse = false;
      }

      if (keyboard_state[SDL_SCANCODE_A]) {
         cameraObject.move( {cameraSpeedPerFrame, 0, 0} );
      }
      else if (keyboard_state[SDL_SCANCODE_D]) {
         cameraObject.move( {-cameraSpeedPerFrame, 0, 0} );
      }

      if (keyboard_state[SDL_SCANCODE_W]) {
         cameraObject.move( {0, 0, cameraSpeedPerFrame} );
      }
      else if (keyboard_state[SDL_SCANCODE_S]) {
         cameraObject.move( {0, 0, -cameraSpeedPerFrame} );
      }

      if (keyboard_state[SDL_SCANCODE_SPACE]) {
         cameraObject.move( {0, cameraSpeedPerFrame, 0} );
      }
      else if (keyboard_state[SDL_SCANCODE_LCTRL]) {
         cameraObject.move( {0, -cameraSpeedPerFrame, 0} );
      }

      if (keyboard_state[SDL_SCANCODE_LEFT]) {
         cameraObject.yaw(-cameraSpeedPerFrame);
      }
      else if (keyboard_state[SDL_SCANCODE_RIGHT]) {
         cameraObject.yaw(cameraSpeedPerFrame);
      }

      if (keyboard_state[SDL_SCANCODE_UP]) {
         cameraObject.pitch(-cameraSpeedPerFrame);
      }
      else if (keyboard_state[SDL_SCANCODE_DOWN]) {
         cameraObject.pitch(cameraSpeedPerFrame);
      }

      cameraObject.pitch(mouseSpeedY * 0.008);
      cameraObject.yaw(mouseSpeedX * 0.008);

      glUniformMatrix4fv(
         glGetUniformLocation(shaderProgram.m_handle, "view"),
         1, GL_FALSE, cameraObject.mtx00());

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      boxObject.rotate(rotSpeed*Clock::sec(FRAME_DURATION), rotAxis);
      for (const auto& pos : cubePositions)
      {
         boxObject.setPosition(pos);
         glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram.m_handle, "model"),
            1, GL_FALSE, boxObject.mtx00());

         boxModel1.bind();
         boxModel1.draw();
      }

      SDL_GL_SwapWindow( window );

      ClockTime now = Clock::now();
      ClockTime duration = now - last_tick;
      if (duration < FRAME_DURATION)
      {
         SDL_Delay( Clock::ms(FRAME_DURATION - duration) );
      }
      last_tick = now;
   }

   glDeleteTextures(1, &texture1);
   glDeleteProgram(shaderProgram.m_handle);

   SDL_GL_DeleteContext( context );
   SDL_DestroyWindow( window );
   SDL_Quit();

   return 0;
}