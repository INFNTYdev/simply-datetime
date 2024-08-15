
#include<gtest/gtest.h>

#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"


// Testing related to VDate calculations
namespace VDateCalculationTests {

	// Maximum number of days to test in succession (Min. date -> Max. date)
	const uint32_t MAX_TESTING_DAYS{ (VDate::MAX_JDN - VDate::EPOCH_JDN) };


	// Tests if VDate class yeilds accurate consecutive JDN cardinals
	TEST(VDateDivergenceTestSuite, VDateJDNIntegrityTest)
	{
		// This test relies on an accurate JDN for January 1, 1970
		// IMPORTANT: (Note that VDate JDN system truncates decimal!)

		const uint32_t epochJDN{ VDate::EPOCH_JDN };// Test anchor point
		VDate sampleDate{ epochJDN };// Test variable

		uint32_t lastJDN{ (epochJDN - (uint32_t)1Ui32) };

		uint32_t validateCount{ 0 };

		// Confirm lossless VDate JDN initialization
		if (sampleDate != VDate{}) {
			std::cout << std::setw(13)
				<< "[ FAILURE  ] "
				<< "Invalid JDN construction for January 1st, 1970 epoch date: "
				<< sampleDate.toJulianDayNumber()
				<< std::setw(13) << ""
				<< "\n\t\t-> JDN expected: " << epochJDN
				<< " (" << VDate{}.dateStr(VDate::Format::STANDARD) << ")"
				<< "\n\t\t-> JDN recieved: " << sampleDate.toJulianDayNumber()
				<< " (" << VDate{ sampleDate.toJulianDayNumber() }.dateStr(VDate::Format::STANDARD) << ")"
				<< "\n\t\t-> JDN divergence: " << (sampleDate.toJulianDayNumber() - epochJDN)
				<< " days"
				<< '\n' << std::endl;

			FAIL();
		}

		std::cout << '\n' << std::setw(13)
			<< "[ TEST MSG ] "
			<< "Testing all possible dates: ('"
			<< sampleDate.dateStr(VDate::Format::STANDARD)
			<< "' through '"
			<< VDate{ VDate::MAX_JDN }.dateStr(VDate::Format::STANDARD)
			<< "')...\n" << std::endl;

		while (validateCount != MAX_TESTING_DAYS) {

			uint32_t expectedJDN{ (lastJDN + (uint32_t)1Ui32) };

			// Confirm sample date JDN is just one after the previous
			if (sampleDate.toJulianDayNumber() != expectedJDN) {
				std::cout << std::setw(13)
					<< "[ FAILURE  ] "
					<< "JDN divergence located at '"
					<< sampleDate.dateStr(VDate::Format::STANDARD)
					<< "' date:"
					<< std::setw(13) << ""
					<< "\n\t\t-> JDN expected: " << expectedJDN
					<< " (" << VDate{ expectedJDN }.dateStr(VDate::Format::STANDARD) << ")"
					<< "\n\t\t-> JDN recieved: " << sampleDate.toJulianDayNumber()
					<< " (" << VDate{ sampleDate.toJulianDayNumber() }.dateStr(VDate::Format::STANDARD) << ")"
					<< "\n\t\t-> JDN divergence: " << (sampleDate.daysUntil(VDate{ expectedJDN }))
					<< " days"
					<< '\n' << std::endl;

				FAIL();
			}

			lastJDN = sampleDate.toJulianDayNumber();
			sampleDate.increase((uint32_t)1Ui32);
			++validateCount;

		}

		// Number of validated days is equal to the max testable days
		ASSERT_EQ(MAX_TESTING_DAYS, validateCount);
	}

	// Tests if VDate class retains lossless JDN system accuracy
	TEST(VDateDivergenceTestSuite, VDateJDNDivergeTest)
	{
		// This test relies on VDate class JDN integrity

		const VDate epochDate{};// Test anchor point
		VDate sampleDate{ epochDate };// Test variable

		const uint32_t epochJDN{ epochDate.toJulianDayNumber() };

		uint32_t validateCount{ 0 };

		uint32_t untilSample{ 0 };

		std::cout << '\n' << std::setw(13)
			<< "[ TEST MSG ] "
			<< "Testing all possible dates: ('"
			<< epochDate.dateStr(VDate::Format::STANDARD)
			<< "' through '"
			<< VDate{ VDate::MAX_JDN }.dateStr(VDate::Format::STANDARD)
			<< "')...\n" << std::endl;

		while (validateCount != MAX_TESTING_DAYS) {

			// VDate::daysUntil() utilizes JDN system**
			untilSample = epochDate.daysUntil(sampleDate);

			// Developer debug breakpoint
			//if (sampleDate.month() == (uint32_t)1Ui32 && sampleDate.day() == (uint32_t)31Ui32)
			//	std::cout << std::endl;// Next loop presents bug

			const uint32_t expectedJDN{ (epochJDN + validateCount) };
			const uint32_t sampleJDN{ sampleDate.toJulianDayNumber() };

			// Verify premise of sample JDN
			if (untilSample != validateCount || expectedJDN != sampleJDN) {
				std::cout << std::setw(13)
					<< "[ FAILURE  ] "
					<< "JDN divergence located at '"
					<< sampleDate.dateStr(VDate::Format::STANDARD)
					<< "' date:"
					<< std::setw(13) << ""
					<< "\n\t\t-> Days from epoch: " << validateCount
					<< "\n\t\t-> Date expected: "
					<< VDate{ expectedJDN }.dateStr(VDate::Format::STANDARD)
					<< "\n\t\t-> JDN expected: " << expectedJDN
					<< "\n\t\t-> JDN recieved: " << sampleDate.toJulianDayNumber()
					<< "\n\t\t-> JDN divergence: " << (sampleJDN - expectedJDN)
					<< " days"
					<< '\n' << std::endl;

				FAIL();
			}

			sampleDate.increase((uint32_t)1Ui32);
			++validateCount;

		}

		// Number of validated days is equal to the max testable days
		ASSERT_EQ(MAX_TESTING_DAYS, validateCount);
	}


	// Tests if VDate class produces accurate day-of-week indecies
	TEST(VDateDivergenceTestSuite, VDateDayOfWeekDivergeTest)
	{
		// This test relies on an accurate day-of-week index for the epoch date

		const VDate epochDate{};// Test anchor point
		VDate sampleDate{ epochDate };// Test variable

		const uint8_t epochDOWIndex{ 4 };

		uint8_t lastDOWIndex{ 3 };

		uint32_t validateCount{ 0 };

		std::cout << '\n' << std::setw(13)
			<< "[ TEST MSG ] "
			<< "Testing all possible dates: ('"
			<< epochDate.dateStr(VDate::Format::STANDARD)
			<< "' through '"
			<< VDate{ VDate::MAX_JDN }.dateStr(VDate::Format::STANDARD)
			<< "')...\n" << std::endl;

		std::string sampleDOWLiteral{ sampleDate.dayOfWeek() };
		uint8_t expectedDOWIndex{ (uint8_t)(lastDOWIndex + (uint8_t)1Ui8) };
		uint8_t sampleDOWIndex{
			simplydt::getDayOfWeekIndex(
				sampleDate.year(),
				sampleDate.month(),
				sampleDate.day()
			)
		};

		// Confirm initial date is epoch date
		if (sampleDate != epochDate) {
			std::cout << std::setw(13)
				<< "[ FAILURE  ] "
				<< "Initial epoch date is incorrect: '"
				<< sampleDate.dateStr(VDate::Format::STANDARD)
				<< '\''
				<< std::setw(13) << ""
				<< "\n\t\t-> Date expected: "
				<< epochDate.dateStr(VDate::Format::STANDARD)
				<< '\n' << std::endl;

			FAIL();
		}

		// Confirm epoch date has correct initial day-of-week
		if (sampleDate == epochDate && sampleDOWLiteral != "Thursday") {
			std::cout << std::setw(13)
				<< "[ FAILURE  ] "
				<< "Epoch date returns incorrect day of week: '"
				<< sampleDOWLiteral
				<< '\''
				<< std::setw(13) << ""
				<< "\n\t\t-> Day-of-week expected: Thursday"
				<< '\n' << std::endl;

			FAIL();
		}

		// Confirm epoch day-of-week is correct index
		if (sampleDate == epochDate && sampleDOWIndex != epochDOWIndex) {
			std::cout << std::setw(13)
				<< "[ FAILURE  ] "
				<< "Library day-of-week index is incorrect: "
				<< (int)sampleDOWIndex
				<< std::setw(13) << ""
				<< "\n\t\t-> Day-of-week index expected: " << (int)epochDOWIndex
				<< '\n' << std::endl;

			FAIL();
		}

		while (validateCount != MAX_TESTING_DAYS) {

			if (validateCount) {
				sampleDOWLiteral = sampleDate.dayOfWeek();
				expectedDOWIndex = (uint8_t)(lastDOWIndex + (uint8_t)1Ui8);
				sampleDOWIndex = simplydt::getDayOfWeekIndex(
					sampleDate.year(),
					sampleDate.month(),
					sampleDate.day()
				);
			}

			// Indecies are 0 (Sunday) - 6 (Saturday)
			if (expectedDOWIndex > (uint8_t)6Ui8)
				expectedDOWIndex = (uint8_t)0Ui8;

			// Update last day-of-week index
			lastDOWIndex = expectedDOWIndex;

			// Confirm day-of-week index is just one ahead of the previous
			if (sampleDOWIndex != expectedDOWIndex) {
				std::cout << std::setw(13)
					<< "[ FAILURE  ] "
					<< "Day-of-week divergence located at '"
					<< sampleDate.dateStr(VDate::Format::STANDARD)
					<< "' date:"
					<< std::setw(13) << ""
					<< "\n\t\t-> Days from epoch: " << validateCount
					<< "\n\t\t-> Day-of-week expected: "
					<< simplydt::Day::DaysOfWeek[expectedDOWIndex]
					<< "\n\t\t-> Day-of-week recieved: "
					<< sampleDOWLiteral
					<< '\n' << std::endl;

				FAIL();
			}

			sampleDate.increase((uint32_t)1Ui32);
			++validateCount;

		}

		// Number of validated days is equal to the max testable days
		ASSERT_EQ(MAX_TESTING_DAYS, validateCount);
	}


	TEST(VDateDivergenceTestSuite, VDateLargeDisplaceDivergeTest)
	{
		//
	}

}
