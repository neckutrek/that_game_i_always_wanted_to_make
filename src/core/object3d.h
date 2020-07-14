#ifndef __THATGAME_CORE_OBJECT3D_INCGRD__
#define __THATGAME_CORE_OBJECT3D_INCGRD__

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace tg
{

class Object3D
{
   glm::mat4 m_model_mtx;

public:
   Object3D()
   : m_model_mtx(glm::mat4(1.0f))
   {}

   void setPosition(glm::vec3 pos)
   {
      m_model_mtx[3][0] = pos[0];
      m_model_mtx[3][1] = pos[1];
      m_model_mtx[3][2] = pos[2];
   }

   void translate(glm::vec3 stretch)
   {
      m_model_mtx = glm::translate(m_model_mtx, stretch);
   }

   void rotate(float radians, glm::vec3 rotationAxis)
   {
      m_model_mtx = glm::rotate(m_model_mtx, radians, rotationAxis);
   }

   const glm::mat4& mtx() const
   {
      return m_model_mtx;
   }

   const float* mtx00() const
   {
      return &m_model_mtx[0][0];
   }

};

} // namespace tg

#endif
