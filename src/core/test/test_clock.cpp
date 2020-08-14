#include "gtest/gtest.h"

#include "core/clock.h"

#include <chrono>
#include <thread>

using namespace tg;

TEST(core__clock, core__clock_time_ctor)
{
   ClockTime t0;
   EXPECT_EQ(t0.sec, 0u);
   EXPECT_EQ(t0.usec, 0u);

   ClockTime t1(1u, 2u);
   EXPECT_EQ(t1.sec, 1u);
   EXPECT_EQ(t1.usec, 2u);
}

TEST(core__clock, core__clock_time_operator_plus)
{
   ClockTime t0(2u, 3u);
   ClockTime t1(2u, 3u);
   ClockTime t2(2u, 1'000'003u);

   ClockTime t3 = t0 + t1;
   EXPECT_EQ(t3.sec, 4u);
   EXPECT_EQ(t3.usec, 6u);

   ClockTime t4 = t0 + t2;
   EXPECT_EQ(t4.sec, 5u);
   EXPECT_EQ(t4.usec, 6u);
}

TEST(core__clock, core__clock_time_operator_minus)
{
   ClockTime t0 = ClockTime(2u, 3u) - ClockTime(3u, 1u);
   EXPECT_EQ(t0.sec, 0u);
   EXPECT_EQ(t0.usec, 0u);

   ClockTime t1 = ClockTime(2u, 3u) - ClockTime(2u, 4u);
   EXPECT_EQ(t1.sec, 0u);
   EXPECT_EQ(t1.usec, 0u);

   ClockTime t2 = ClockTime(2u, 3u) - ClockTime(2u, 3u);
   EXPECT_EQ(t2.sec, 0u);
   EXPECT_EQ(t2.usec, 0u);

   ClockTime t3 = ClockTime(5u, 3u) - ClockTime(2u, 1u);
   EXPECT_EQ(t3.sec, 3u);
   EXPECT_EQ(t3.usec, 2u);

   ClockTime t4 = ClockTime(5u, 3u) - ClockTime(2u, 7u);
   EXPECT_EQ(t4.sec, 3u - 1u);
   EXPECT_EQ(t4.usec, 1'000'000u - 4u);
}

TEST(core__clock, core__clock_time_operator_comparison)
{
   EXPECT_TRUE ( ClockTime(3u, 2u) > ClockTime(1u, 2u) );
   EXPECT_TRUE ( ClockTime(3u, 3u) > ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(1u, 2u) > ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(3u, 2u) > ClockTime(3u, 3u) );
   EXPECT_FALSE( ClockTime(3u, 2u) > ClockTime(3u, 2u) );

   EXPECT_TRUE ( ClockTime(3u, 2u) >= ClockTime(1u, 2u) );
   EXPECT_TRUE ( ClockTime(3u, 3u) >= ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(1u, 2u) >= ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(3u, 2u) >= ClockTime(3u, 3u) );
   EXPECT_TRUE ( ClockTime(3u, 2u) >= ClockTime(3u, 2u) );

   EXPECT_TRUE ( ClockTime(2u, 2u) < ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(3u, 2u) < ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(3u, 3u) < ClockTime(3u, 2u) );

   EXPECT_TRUE ( ClockTime(2u, 2u) <= ClockTime(3u, 2u) );
   EXPECT_TRUE ( ClockTime(3u, 2u) <= ClockTime(3u, 2u) );
   EXPECT_FALSE( ClockTime(3u, 3u) <= ClockTime(3u, 2u) );

   EXPECT_TRUE ( ClockTime(1u, 2u) == ClockTime(1u, 2u) );
   EXPECT_FALSE( ClockTime(1u, 2u) == ClockTime(2u, 2u) );
   EXPECT_FALSE( ClockTime(1u, 2u) == ClockTime(1u, 1u) );
   EXPECT_FALSE( ClockTime(1u, 2u) == ClockTime(3u, 3u) );

   EXPECT_FALSE( ClockTime(1u, 2u) != ClockTime(1u, 2u) );
   EXPECT_TRUE ( ClockTime(1u, 2u) != ClockTime(2u, 2u) );
   EXPECT_TRUE ( ClockTime(1u, 2u) != ClockTime(1u, 1u) );
   EXPECT_TRUE ( ClockTime(1u, 2u) != ClockTime(3u, 3u) );
}

TEST(core__clock, core__clock_now)
{
   ClockTime t1 = Clock::now();
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   ClockTime t2 = Clock::now() - t1;
   EXPECT_EQ(t2.sec, 0u);
   EXPECT_GT(t2.usec, 50'000u);
   EXPECT_LT(t2.usec, 150'000u);
}

TEST(core__clock, core__clock_ms)
{
   EXPECT_EQ( Clock::ms(ClockTime(0u, 5'123u)), 5u );
   EXPECT_EQ( Clock::ms(ClockTime(1u, 5'123u)), 1005u );
   EXPECT_EQ( Clock::ms(ClockTime(1u, 5'987u)), 1005u );

   EXPECT_EQ( Clock::ms(5u), ClockTime(0u, 5'000u) );
   EXPECT_EQ( Clock::ms(1005u), ClockTime(1u, 5'000u) );
   EXPECT_EQ( Clock::ms(1995u), ClockTime(1u, 995'000u) );
}

TEST(core__clock, core__clock_sec)
{
   EXPECT_EQ( Clock::sec(ClockTime(6u, 5'123u)), 6.005123f );
}