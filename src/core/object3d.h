#ifndef __THATGAME_CORE_OBJECT3D_INCGRD__
#define __THATGAME_CORE_OBJECT3D_INCGRD__

#include "core/object3d_interface.h"

#include "glm/glm.hpp"

#include <vector>

namespace tg
{

class Object3D : public Object3DInterface
{
public:
                           Object3D();
   virtual                 ~Object3D() = default;
                           Object3D(const Object3D&) = default;
                           Object3D(Object3D&&) = default;
                           Object3D& operator=(const Object3D&) = default;
                           Object3D& operator=(Object3D&&) = default;

   virtual  void           setPosition(glm::vec3 pos);                           // [world coordinates]
   virtual  void           translate(glm::vec3 stretch);                         // [world coordinates]
   virtual  void           rotate(float radians, glm::vec3 rotationAxis);        // [world coordinates]

   virtual  glm::vec3      getPosition() const;                                  // [world coordinates]

   virtual  const glm::mat4& mtx() const;
   virtual  const float*   mtx00() const;

private:
            glm::mat4      m_model_mtx;

};

} // namespace tg

#endif
