#include "core/object3d.h"

#include "glm/gtx/transform.hpp"

namespace tg
{

Object3D::Object3D()
: m_model_mtx(glm::mat4(1.0f))
{}

glm::vec3 Object3D::getPosition() const
{
   return glm::vec3(m_model_mtx[3]);
}

const glm::mat4& Object3D::mtx() const
{
   return m_model_mtx;
}

const float* Object3D::mtx00() const
{
   return &mtx()[0][0];
}

void Object3D::rotate(float radians, glm::vec3 rotationAxis)
{
   m_model_mtx = glm::rotate(m_model_mtx, radians, rotationAxis);
}

void Object3D::setPosition(glm::vec3 pos)
{
   for (auto i : {0,1,2})
      m_model_mtx[3][i] = pos[i];
}

void Object3D::translate(glm::vec3 stretch)
{
   m_model_mtx = glm::translate(m_model_mtx, stretch);
}

} // namespace tg
