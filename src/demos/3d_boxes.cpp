#include "core/glad.h"
#include <GLFW/glfw3.h>

#include "core/shader_types.h"
#include "core/shader_builder.h"
#include "core/vertex_object.h"
#include "core/texture_loading.h"
#include "core/object3d.h"

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

   glEnable(GL_DEPTH_TEST);

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

   Object3D boxObject;
   boxObject.translate({0.1f, 0.2f, 0.3f});
   float angle = 45.0f;
   glm::vec3 rotAxis = {1.0f, 1.0f, 1.0f};
   boxObject.rotate(glm::radians(angle), rotAxis);

   glUniformMatrix4fv(
      glGetUniformLocation(shaderProgram.m_handle, "model"),
      1, GL_FALSE, boxObject.mtx00());

   while(!glfwWindowShouldClose(window))
   {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      boxModel1.bind();
      boxModel1.draw();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glDeleteTextures(1, &texture1);
   glDeleteProgram(shaderProgram.m_handle);

   glfwTerminate();
   return 0;
}