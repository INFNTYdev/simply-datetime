
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//    DATETIME STRING UTILITY TESTS     //
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//



#include<gtest/gtest.h>
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


namespace DTStringUtilityTests {

	TEST(GregorianCalendarUtilityTestSuite, DetectLeapYear)
	{
		std::vector<std::pair<uint16_t, bool>> testSet{
			{ 2032, true },
			{ 2024, true },
			{ 2008, true },
			{ 2000, true },
			{ 1996, true },
			{ 1985, false },
			{ 1977, false },
			{ 1970, false },
		};

		for (std::pair<uint16_t, bool>& set : testSet) {

			const uint16_t* sample = &set.first;
			const bool* expect = &set.second;

			ASSERT_EQ(SimplyDt::GregorianCalendar::Util::isLeapYear(*sample), *expect);

		}
	}

}
