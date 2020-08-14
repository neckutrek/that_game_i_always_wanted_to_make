#ifndef __THATGAME_CORE_OBJECT3D_INTERFACE_INCGRD__
#define __THATGAME_CORE_OBJECT3D_INTERFACE_INCGRD__

#include <vector>

#include "glm/glm.hpp"

namespace tg
{

class Object3DInterface
{
public:
                           Object3DInterface() = default;
   virtual                 ~Object3DInterface() = default;
                           Object3DInterface(const Object3DInterface&) = default;
                           Object3DInterface(Object3DInterface&&) = default;
                           Object3DInterface& operator=(const Object3DInterface&) = default;
                           Object3DInterface& operator=(Object3DInterface&&) = default;

   virtual  void           setPosition(glm::vec3 pos) = 0;                       // [world coordinates]
   virtual  void           translate(glm::vec3 stretch) = 0;                     // [world coordinates]
   virtual  void           rotate(float radians, glm::vec3 rotationAxis) = 0;    // [world coordinates]

   virtual  glm::vec3      getPosition() const = 0;                              // [world coordinates]

   virtual  const glm::mat4& mtx() const = 0;
   virtual  const float*   mtx00() const = 0;

};

} // namespace tg

#endif
