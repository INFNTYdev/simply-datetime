
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
//    COORDINATED UNIVERSAL TIME UTILITY TESTS    \\
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\



#include<gtest/gtest.h>
#include"simplydt/coord_universal_time/utc_util.hpp"


namespace CoordinatedUniversalTimeTests {

	TEST(UTCUtilityTestSuite, DetermineUTCTimeFromJDN)
	{
		using Time = SimplyDt::CoordUniversalTime::Time;
		using JDN = SimplyDt::JulianCalendar::JDN;

		std::vector<std::pair<JDN, Time>> testSet{
			{0., {.hour=12, .minute=0, .second=0}},
		};

		for (std::pair<JDN, Time>& set : testSet) {

			const JDN* sample = &set.first;
			const Time* expect = &set.second;

			Time time{};

			SimplyDt::CoordUniversalTime::Util::jdnToUtc(*sample, time);

			ASSERT_EQ(time.hour, expect->hour);
			ASSERT_EQ(time.minute, expect->minute);
			ASSERT_EQ(time.second, expect->second);

		}
	}

}
