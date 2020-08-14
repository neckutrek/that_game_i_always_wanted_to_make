#include "gtest/gtest.h"

#include "glm/glm.hpp"

#include "core/utilities.h"

#include "core/test/utilities.h"

#define private public
#include "core/camera.h"

using namespace tg;
using namespace tg_test;

class core__camera : public testing::Test
{
protected:
            Camera         m_camera;

                           core__camera()
                           : m_camera()
                           {}

   void debug() {using namespace tg; std::cout << m_camera.mtx() << std::endl;}
};

TEST_F(core__camera, core__camera_ctor)
{
   EXPECT_NEAR(m_camera.m_pitch, M_PI/2.0f, ABS_ERROR);
   EXPECT_NEAR(m_camera.m_yaw, M_PI, ABS_ERROR);
   EXPECT_EQ(m_camera.m_up, glm::vec3(0.0f, 1.0f, 0.0f));
   EXPECT_EQ(m_camera.m_position, glm::vec3(0.0f, 0.0f, 0.0f));
   EXPECT_NEAR(m_camera.m_changed, false, ABS_ERROR);
   compareMatrix( m_camera.mtx(), glm::mat4(1.0f) );
}

TEST_F(core__camera, core__camera_get_set_position)
{
   EXPECT_EQ( m_camera.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f) );

   glm::vec3 pos = {1.0f, 2.0f, 3.0f};
   m_camera.setPosition( pos );
   EXPECT_EQ( m_camera.getPosition(), pos );
}

TEST_F(core__camera, core__camera_translate)
{
   glm::vec3 d = {1.0, 2.0, 3.0};
   m_camera.translate( d );
   EXPECT_EQ( m_camera.getPosition(), d );

   m_camera.translate( -2.0f*d );
   EXPECT_EQ( m_camera.getPosition(), -d );

   m_camera.translate( d );
   EXPECT_EQ( m_camera.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f) );
}

TEST_F(core__camera, core__camera_mtx_mtx00)
{
   const glm::mat4& m = m_camera.mtx();
   const float* p = m_camera.mtx00();
   EXPECT_EQ( p, &m[0][0] );
}

TEST_F(core__camera, core__camera_rotate)
{
   glm::vec3 pos({1,2,3});
   m_camera.setPosition(pos);
   m_camera.rotate(M_PI, {1,1,1});

   glm::mat4 m = {
      { -0.333333, -0.628540,  0.702728,  0.000000 },
      {  0.000000,  0.745356,  0.666667,  0.000000 },
      { -0.942809,  0.222222, -0.248452,  0.000000 },
      {  3.161761, -1.528839, -1.290706,  1.000000 } };
  compareMatrix( m_camera.mtx(), m );
}

TEST_F(core__camera, core__camera_look_at)
{
   glm::vec3 p1 = {1, 2, 3};
   glm::vec3 p2 = {-1, 2, 3};
   m_camera.setPosition( p1 );
   m_camera.lookAt( p2 );

   glm::mat4 m = glm::lookAt(p1, p2, m_camera.upward() );
   compareMatrix(m_camera.mtx(), m);
}

TEST_F(core__camera, core__camera_move)
{
   m_camera.pitch(-M_PI/4);
   m_camera.yaw(-M_PI/4);
   glm::vec3 stretch = {1,2,3};
   m_camera.move( stretch );

   glm::vec3 pos = {-1.292893, 3.121320, -0.292893};
   for (int i=0; i<3; ++i)
      EXPECT_NEAR( m_camera.getPosition()[i], pos[i], 0.00001 );
}

TEST_F(core__camera, core__camera_pitch)
{
   m_camera.pitch(-M_PI/4);
   EXPECT_NEAR(m_camera.m_pitch, M_PI/2.0f - M_PI/4.0f, ABS_ERROR);
}

TEST_F(core__camera, core__camera_yaw)
{
   m_camera.yaw(-M_PI/4);
   EXPECT_NEAR(m_camera.m_yaw, M_PI - M_PI/4.0f, ABS_ERROR);
}

TEST_F(core__camera, core__camera_forward)
{
   glm::vec3 f = m_camera.forward();
   glm::vec3 f2 = {0,0,-1};
   for (int i=0; i<3; ++i)
      EXPECT_NEAR(f[i], f2[i], ABS_ERROR);
}

TEST_F(core__camera, core__camera_upward)
{
   glm::vec3 f = m_camera.upward();
   glm::vec3 f2 = {0,1,0};
   for (int i=0; i<3; ++i)
      EXPECT_NEAR(f[i], f2[i], ABS_ERROR);
}

TEST_F(core__camera, core__camera_leftward)
{
   glm::vec3 f = m_camera.leftward();
   glm::vec3 f2 = {-1,0,0};
   for (int i=0; i<3; ++i)
      EXPECT_NEAR(f[i], f2[i], ABS_ERROR);
}
