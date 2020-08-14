#ifndef __THATGAME_CORE_UTILITIES_INCGRD__
#define __THATGAME_CORE_UTILITIES_INCGRD__

#include <ostream>

#include "glm/glm.hpp"

namespace tg
{

template <int N>
std::ostream& operator<<(std::ostream& os, const glm::vec<N, float, glm::defaultp>& vec);

template <int N>
std::ostream& operator<<(std::ostream& os, const glm::mat<N, N, float, glm::defaultp>& mat);

} // namespace tg

#include "core/utilities.hpp"

#endif
