#include <iomanip>

static const char* DELIMITER = ", ";
static unsigned int PRECISION = 6;

namespace
{
   template <typename T>
   std::ostream& print(std::ostream& os, const T& vec)
   {
      size_t size = static_cast<size_t>(vec.length());
      os << std::fixed << std::setprecision(PRECISION);
      for (size_t i=0; i<size; ++i)
      {
         os << (vec[i] < 0.0f ? "" : " ") << vec[i];
         os << (i < size-1 ? DELIMITER : "");
      }
      os << std::resetiosflags(std::ios_base::fixed);
      return os;
   }
}

namespace tg
{

template <int N>
std::ostream& operator<<(std::ostream& os, const glm::vec<N, float, glm::defaultp>& vec)
{
   os << "{ ";
   ::print(os, vec);
   os << " }";
   return os;
}

template <int N>
std::ostream& operator<<(std::ostream& os, const glm::mat<N, N, float, glm::defaultp>& mat)
{
   size_t size = static_cast<size_t>(mat.length());
   os << "{ ";
   for (size_t i=0; i<size-1; ++i)
   {
      os << mat[i] << ",\n  ";
   }
   os << mat[size-1] << " }";
   return os;
}

} // namespace tg