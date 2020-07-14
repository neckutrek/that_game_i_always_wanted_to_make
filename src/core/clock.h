#ifndef __THATGAME_CORE_CLOCK_INCGRD__
#define __THATGAME_CORE_CLOCK_INCGRD__

namespace tg
{

struct ClockTime
{
            unsigned int   sec;  // seconds since dawn of time
            unsigned int   usec; // microseconds since last second (usec < 1'000'000)

                           ClockTime();

                           ClockTime(unsigned int sec, unsigned int usec);

            ClockTime      operator+(const ClockTime& t) const;

            ClockTime      operator-(const ClockTime& t) const;

            bool           operator>(const ClockTime& t) const;
            bool           operator>=(const ClockTime& t) const;
            bool           operator<(const ClockTime& t) const;
            bool           operator<=(const ClockTime& t) const;
            
            bool           operator==(const ClockTime& t) const;
            bool           operator!=(const ClockTime& t) const;
};

namespace Clock
{
   /// Returns time since the global clock started (dawn of time)
   tg::ClockTime now();

   // Convert milliseconds to ClockTime
   tg::ClockTime ms(unsigned int ms);
   unsigned int ms(const tg::ClockTime& t);
}

} // namespace tg

#endif
