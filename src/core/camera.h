#ifndef __THATGAME_CORE_CAMERA_INCGRD__
#define __THATGAME_CORE_CAMERA_INCGRD__

#include "core/object3d_interface.h"
#include "core/utilities.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include <iostream>

namespace tg
{

class Camera : public Object3DInterface
{
public:
                           Camera();
   virtual                 ~Camera() = default;
                           Camera(const Camera&) = default;
                           Camera(Camera&&) = default;
                           Camera& operator=(const Camera&) = default;
                           Camera& operator=(Camera&&) = default;

   // Object3DInterface
   virtual  void           setPosition(glm::vec3 pos);                           // [world coordinates]
   virtual  void           translate(glm::vec3 stretch);                         // [world coordinates]
   virtual  void           rotate(float radians, glm::vec3 rotationAxis);        // [world coordinates]

   virtual  glm::vec3      getPosition() const;                                  // [world coordinates]

   virtual  const glm::mat4& mtx() const;
   virtual  const float*   mtx00() const;

   // Camera
            void           lookAt(glm::vec3 pos);                                // [world coordinates]
            void           move(glm::vec3 stretch);                              // [model coordinates]

            void           pitch(float radians);
            void           yaw(float radians);

            glm::vec3      forward() const;     // [world coordinates] unit vector pointing forward
            glm::vec3      upward() const;      // [world coordinates] unit vector pointing upward
            glm::vec3      leftward() const;    // [world coordinates] unit vector pointing leftward

private:
   // State data
            float          m_pitch;    // [rad] angle around x-axis in model coordinates
            float          m_yaw;      // [rad] angle around y-axis in model coordinates

            glm::vec3      m_up;       // [world coordinates]
            glm::vec3      m_position; // [world coordinates]

   // Auxiliary data-structure
   mutable  bool           m_changed;  // flag for keeping track of state changes
   mutable  glm::mat4      m_model_mtx;
};

} // namespace tg

#endif
