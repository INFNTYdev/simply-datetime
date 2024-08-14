
#include<gtest/gtest.h>

#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"


// Testing related to VDate calculations
namespace VDateCalculationTests {

	// Maximum number of days to test in succession (Min. date -> Max. date)
	const uint32_t MAX_TESTING_DAYS{ (VDate::MAX_JDN - VDate::EPOCH_JDN) };

	// Tests if VDate class retains lossless JDN system accuracy
	TEST(VDateDivergenceTestSuite, VDateJDNDivergeTest)
	{
		// This test relies on VDate class JDN integrity
		// NOTE: Need a test that verifies calculated JDN accuracy
		//		-> (HTTPS requests to JDN form on AVSSO website?)
		//		-> (Compile attainable dates correct JDN and compare?)
		//			-> (Use Python to compile 'answer key' file?)

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

}
