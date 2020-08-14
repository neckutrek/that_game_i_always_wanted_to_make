#include "core/clock.h"

#include <chrono>
#include <cassert>
#include <cmath>

namespace tg
{

ClockTime::ClockTime() : sec(0u), usec(0u) {}
ClockTime::ClockTime(unsigned int sec, unsigned int usec) : sec(sec), usec(usec) {}

ClockTime ClockTime::operator+(const ClockTime& t) const {
   unsigned int s = sec+t.sec;
   unsigned int u = usec+t.usec;
   unsigned int x = u / 1'000'000;
   s += x;
   u -= x * 1'000'000;
   return ClockTime(s, u);
}

ClockTime ClockTime::operator-(const ClockTime& t) const {
   if (t.sec > sec || (t.sec == sec && t.usec >= usec))
   {
      return ClockTime(0u, 0u);
   }

   unsigned int s = sec-t.sec;
   unsigned int u = usec - t.usec;
   if (t.usec > usec)
   {
      s -= 1;
      u = 1'000'000 + usec - t.usec;
   }

   return ClockTime(s, u);
}

bool ClockTime::operator>(const ClockTime& t) const
{
   return sec > t.sec || (sec == t.sec && usec > t.usec);
}

bool ClockTime::operator>=(const ClockTime& t) const
{
   return sec > t.sec || (sec == t.sec && usec >= t.usec);
}

bool ClockTime::operator<(const ClockTime& t) const
{
   return !(*this >= t);
}

bool ClockTime::operator<=(const ClockTime& t) const
{
   return !(*this > t);
}

bool ClockTime::operator==(const ClockTime& t) const
{
   return sec == t.sec && usec == t.usec;
}

bool ClockTime::operator!=(const ClockTime& t) const
{
   return !(*this == t);
}

namespace Clock
{
   tg::ClockTime now()
   {
      using ClockT = std::chrono::high_resolution_clock;

      static auto start_time = ClockT::now();
      auto now = ClockT::now();

      unsigned int sec = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();

      auto just_now = std::chrono::floor<std::chrono::seconds>(now);
      unsigned int usec = std::chrono::duration_cast<std::chrono::microseconds>(now - just_now).count();

      assert(usec < 1'000'000);

      return {sec, usec};
   }

   tg::ClockTime ms(unsigned int ms)
   {
      unsigned int s = ms / 1'000;
      return ClockTime(s, (ms - s * 1'000) * 1'000);
   }

   unsigned int ms(const tg::ClockTime& t)
   {
      return t.sec * 1'000 + t.usec / 1'000;
   }

   tg::ClockTime sec(float sec)
   {
      if (sec < 0) return ClockTime(0, 0);
      float frac, integral;
      frac = std::modf(sec, &integral);
      unsigned int s = static_cast<unsigned int>(integral);
      unsigned int us = static_cast<unsigned int>(frac * 1'000'000.0f);
      return ClockTime(s, us);
   }

   float sec(const tg::ClockTime& t)
   {
      return static_cast<float>(t.sec) + static_cast<float>(t.usec) / 1'000'000.0f;
   }
}

} // namespace tg
