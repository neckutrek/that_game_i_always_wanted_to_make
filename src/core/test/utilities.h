#ifndef __THATGAME_TEST_UTILITIES_INCGRD__
#define __THATGAME_TEST_UTILITIES_INCGRD__

#include "glm/glm.hpp"

namespace tg_test
{

static constexpr float ABS_ERROR = 0.0001f;

template <int N>
void compareMatrix(
   const glm::mat<N, N, float, glm::defaultp>& m1,
   const glm::mat<N, N, float, glm::defaultp>& m2)
{
   for (int r=0; r<N; ++r)
      for (int c=0; c<N; ++c)
         EXPECT_NEAR(m1[r][c], m2[r][c], ABS_ERROR) << "r=" << r << " c=" << c;
}

} // namespace tg_test

#endif