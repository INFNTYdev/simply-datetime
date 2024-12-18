
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
//    GREGORIAN CALENDAR UTILITY TESTS    \\
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\



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

	TEST(GregorianCalendarUtilityTestSuite, DetermineTotalDaysInMonth)
	{
		std::vector<std::pair<std::pair<uint16_t, uint8_t>, uint8_t>> testSet{
			{{2024, 12}, 31},    // December 2024
		};

		for (std::pair<std::pair<uint16_t, uint8_t>, uint8_t>& set : testSet) {

			const uint16_t* sampleYear = &set.first.first;
			const uint8_t* sampleMonth = &set.first.second;
			const uint8_t* expect = &set.second;

			ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getMonthTotalDays(*sampleYear, *sampleMonth), *expect);

		}
	}

	TEST(GregorianCalendarUtilityTestSuite, DetermineTotalDaysInYear)
	{
		std::vector<std::pair<uint16_t, uint16_t>> testSet{
			{2024, 366},
			{2001, 365},
		};

		for (std::pair<uint16_t, uint16_t>& set : testSet) {

			const uint16_t* sample = &set.first;
			const uint16_t* expect = &set.second;

			ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getYearTotalDays(*sample), *expect);

		}
	}

	TEST(GregorianCalendarUtilityTestSuite, DetermineMonthIndex)
	{
		uint8_t sample{ 255 };

		while (sample >= (uint8_t)0) {

			const bool isValidIndex = (sample >= 1 && sample <= 12);

			if (isValidIndex) {
				const uint8_t expect{ (uint8_t)(sample - 1) };
				ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getMonthIndex(sample), expect);
			}
			else
				ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getMonthIndex(sample), 0);

			if (sample == 0)
				break;

			--sample;

		}
	}

	TEST(GregorianCalendarUtilityTestSuite, DetermineMonthLiteralFromInteger)
	{
		std::vector<std::pair<uint8_t, std::string>> testSet{
			{1, "January"},
			{2, "February"},
			{3, "March"},
			{4, "April"},
			{5, "May"},
			{6, "June"},
			{7, "July"},
			{8, "August"},
			{9, "September"},
			{10, "October"},
			{11, "November"},
			{12, "December"}
		};

		uint8_t sample{ 255 };

		while (sample >= (uint8_t)0) {

			const bool isValidIndex = (sample >= 1 && sample <= 12);

			if (isValidIndex) {
				const char* expect = testSet[sample - 1].second.data();
				ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getMonth(sample), expect);
			}
			else {
				const char* expect{ nullptr };
				ASSERT_EQ(SimplyDt::GregorianCalendar::Util::getMonth(sample), expect);
			}

			if (sample == 0)
				break;

			--sample;

		}
	}

	TEST(GregorianCalendarUtilityTestSuite, DetermineDateDayOfWeekIndex)
	{
		std::vector<std::pair<SimplyDt::GregorianCalendar::Date, uint8_t>> testSet{
			{{.year=2024, .month=12, .day=18}, 3},
		};

		for (std::pair<SimplyDt::GregorianCalendar::Date, uint8_t>& set : testSet) {

			const uint16_t* sampleYear = &set.first.year;
			const uint8_t* sampleMonth = &set.first.month;
			const uint8_t* sampleDay = &set.first.day;
			const uint8_t* expect = &set.second;

			ASSERT_EQ(
				SimplyDt::GregorianCalendar::Util::getDayOfWeekIndex(
					*sampleYear,
					*sampleMonth,
					*sampleDay
				),
				*expect
			);

		}
	}

}
