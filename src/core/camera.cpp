#include "core/camera.h"

#include "core/utilities.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

namespace
{
   /// definition of the pitch/yaw orientation in world coordinates
   /// pitch is the angle from the y-axis in any plane containing the y-axis
   /// yaw if the angle form the z-axis in the xz-plane
   glm::vec3 direction(float pitch, float yaw)
   {
      return glm::vec3(
         -std::sin(pitch) * std::sin(yaw),
         std::cos(pitch),
         std::sin(pitch) * std::cos(yaw)
      );
   }

   auto direction(glm::vec3 vec)
   {
      glm::vec3 upward = direction(0.0f, 0.0f);
      glm::vec3 leftward = direction(M_PI/2.0f, 0.0f);

      float udot = glm::dot(upward, vec);
      float ldot = glm::dot(leftward, vec);

      float pitch = std::acosf( udot );
      float yaw = std::acosf( ldot );

      if (udot < 0)
      {
         if (pitch < 0) pitch += 2*M_PI;
         else           pitch -= 2*M_PI;
      }

      if (ldot < 0)
      {
         if (yaw < 0) yaw += 2*M_PI;
         else         yaw -= 2*M_PI;
      }

      return std::make_tuple(pitch, yaw);
   }
}

namespace tg
{

Camera::Camera()
: m_pitch(M_PI/2.0),
  m_yaw(M_PI),
  m_up(0.0f, 1.0f, 0.0f),
  m_position(0.0f, 0.0f, 0.0f)
{
   m_changed = true;
   mtx();
}

glm::vec3 Camera::forward() const
{
   return direction(m_pitch, m_yaw);
}

glm::vec3 Camera::getPosition() const
{
   return m_position;
}

glm::vec3 Camera::leftward() const
{
   return cross(m_up, forward());
}

void Camera::lookAt(glm::vec3 pos)
{
   std::tie(m_pitch, m_yaw) = direction(pos - m_position);
   m_changed = true;
}

void Camera::move(glm::vec3 stretch)
{
   m_position += stretch[0] * leftward() + stretch[1] * upward() + stretch[2] * forward();
   m_changed = true;
}

const glm::mat4& Camera::mtx() const
{
   if (m_changed)
   {
      m_model_mtx = glm::lookAt( m_position, m_position + forward(), m_up );
      m_changed = false;
   }
   return m_model_mtx;
}

const float* Camera::mtx00() const
{
   return &mtx()[0][0];
}

void Camera::pitch(float radians)
{
   m_pitch += radians;
   constexpr float min = 0.00001f;
   constexpr float max = static_cast<float>(M_PI) - std::numeric_limits<float>::epsilon();
   m_pitch = std::clamp(m_pitch, min, max);
   m_changed = true;
}

void Camera::rotate(float radians, glm::vec3 rotationAxis)
{
   glm::mat3 r = glm::rotate(radians, rotationAxis);
   glm::vec3 f = r * forward();
   std::tie(m_pitch, m_yaw) = direction(f);
}

void Camera::setPosition(glm::vec3 pos)
{
   m_position = pos;
   m_changed = true;
}

void Camera::translate(glm::vec3 stretch)
{
   m_position += stretch;
   m_changed = true;
}

glm::vec3 Camera::upward() const
{
   return cross(forward(), leftward());
}

void Camera::yaw(float radians)
{
   m_yaw += radians;
   m_yaw = fmod(m_yaw, 2*M_PI);
	if (m_yaw < 0)
   {
      m_yaw += 2*M_PI;
   }
   m_changed = true;
}

} // namespace tg
