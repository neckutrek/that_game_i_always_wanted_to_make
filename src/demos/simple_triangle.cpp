#include "core/glad.h"
#include <GLFW/glfw3.h>

#include "core/shader_types.h"
#include "core/shader_builder.h"
#include "core/vertex_object.h"

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

   window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
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
   triangle.setVertices(vertices, 3);
   triangle.bind();

   while(!glfwWindowShouldClose(window))
   {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      triangle.draw();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glDeleteProgram(shaderProgram.m_handle);

   glfwTerminate();
   return 0;
}