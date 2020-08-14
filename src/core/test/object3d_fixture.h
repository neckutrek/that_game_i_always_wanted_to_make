#include "gtest/gtest.h"

#include "glm/glm.hpp"

#include "core/utilities.h"

#include "core/test/utilities.h"

using namespace tg_test;

template <typename T>
class core__object3d_fixture : public testing::Test
{
protected:
            T              m_object;

                           core__object3d_fixture()
                           : m_object()
                           {}

   void debug() {using namespace tg; std::cout << m_object.mtx() << std::endl;}
};

TYPED_TEST_SUITE_P(core__object3d_fixture);

TYPED_TEST_P(core__object3d_fixture, core__object3d_ctor)
{
   compareMatrix(this->m_object.mtx(), glm::mat4(1.0f) );
}

TYPED_TEST_P(core__object3d_fixture, core__object3d_get_set_position)
{
   EXPECT_EQ( this->m_object.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f) );

   glm::vec3 pos = {1.0f, 2.0f, 3.0f};
   this->m_object.setPosition( pos );
   EXPECT_EQ( this->m_object.getPosition(), pos );

   glm::mat4 m(1.0f);
   for (auto i : {0,1,2}) m[3][i] = pos[i];
   compareMatrix(this->m_object.mtx(), m);
}

TYPED_TEST_P(core__object3d_fixture, core__object3d_translate)
{
   glm::vec3 d = {1.0, 2.0, 3.0};
   this->m_object.translate( d );
   EXPECT_EQ( this->m_object.getPosition(), d );

   this->m_object.translate( -2.0f*d );
   EXPECT_EQ( this->m_object.getPosition(), -d );

   this->m_object.translate( d );
   EXPECT_EQ( this->m_object.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f) );

   EXPECT_EQ( this->m_object.mtx(), glm::mat4(1.0f) );
}

TYPED_TEST_P(core__object3d_fixture, core__object3d_mtx_mtx00)
{
   const glm::mat4& m = this->m_object.mtx();
   const float* p = this->m_object.mtx00();
   EXPECT_EQ( p, &m[0][0] );
}

TYPED_TEST_P(core__object3d_fixture, core__object3d_rotate)
{
   glm::vec3 pos({1,2,3});
   this->m_object.setPosition(pos);

   this->m_object.rotate(M_PI, {1,1,1});

   // glm::mat4 uses column-wise initialization
   glm::mat4 m1{
      { -0.3333,  0.6666,  0.6666,  0},
      {  0.6666, -0.3333,  0.6666,  0},
      {  0.6666,  0.6666, -0.3333,  0},
      {  1,       2,       3,       1} };
   compareMatrix(this->m_object.mtx(), m1);

   this->m_object.rotate(M_PI, {1,1,1});
   glm::mat4 m2(1.0f);
   for (auto i : {0,1,2}) m2[3][i] = pos[i];
   compareMatrix(this->m_object.mtx(),  m2 );
}

REGISTER_TYPED_TEST_SUITE_P(core__object3d_fixture,
   core__object3d_ctor,
   core__object3d_get_set_position,
   core__object3d_translate,
   core__object3d_mtx_mtx00,
   core__object3d_rotate
);
