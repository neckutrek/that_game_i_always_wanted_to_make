#include "core/glad.h"
#include <GLFW/glfw3.h>

#include "core/shader_types.h"
#include "core/shader_builder.h"
#include "core/vertex_object.h"
#include "core/texture_loading.h"

#include <iostream>

using namespace tg;

static constexpr int SCREEN_WIDTH = 1024;
static constexpr int SCREEN_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, true);
   }
}

GLFWwindow* initGlfw()
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return nullptr;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Boxes", NULL, NULL);
   if (!window)
   {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return nullptr;
   }

   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      return nullptr;
   }

   return window;
}

int main()
{
   GLFWwindow* window = initGlfw();
   if (!window)
   {
      return -1;
   }

   Shader vertexShader = ShaderBuilder::buildShader("../src/shaders/pos_col_tex.vert");
   Shader fragmentShader = ShaderBuilder::buildShader("../src/shaders/tex.frag");
   ShaderProgram shaderProgram = ShaderBuilder::linkShaderProgram(vertexShader, fragmentShader);
   ShaderBuilder::deleteShaders(vertexShader, fragmentShader);
   glUseProgram(shaderProgram.m_handle);

   float vertices[] = {
      // positions          // colors           // texture coords
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };

   unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3
   };

   VertexObject<3,3,2> box_side;
   box_side.set(vertices, 4, indices, 2);
   box_side.bind();

   unsigned int texture1 = loadTexture("../assets/container.jpg");
   glBindTexture(GL_TEXTURE_2D, texture1);

   while(!glfwWindowShouldClose(window))
   {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      box_side.draw();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glDeleteTextures(1, &texture1);
   glDeleteProgram(shaderProgram.m_handle);

   glfwTerminate();
   return 0;
}