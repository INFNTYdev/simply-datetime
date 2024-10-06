
#include<gtest/gtest.h>
#include"simplydt/datetime/datetime.hpp"


/* Datetime Class Validity Test Space */
namespace DatetimeClassValidityTests {

	/* Total number of representable dates */
	const uint32_t REPRESENTABLE_COUNT{ static_cast<uint32_t>(Datetime::MAX_JDN - Datetime::EPOCH_JDN) };


	/* Test if Datetime class handles edge dates appropriately */
	TEST(DatetimeValiditySuite, EdgeDatetimeStabilityTest)
	{
		//
	}

	/* Test if Datetime class yields accurate consecutive JDN dates */
	TEST(DatetimeValiditySuite, ConsecutiveJDNCalculationTest)
	{
		const Datetime::JDN epochJDN{ Datetime::EPOCH_JDN };

		// Construct epoch datetime
		Datetime subject{ epochJDN };

		// Confirm initial date is standard library epoch date
		if ((subject.year() != 1970Ui16) || (subject.month() != 1Ui8) || (subject.day() != 1Ui8)) {
			std::cout
				<< std::setw(13) << "[ FAILURE  ] "
				<< "Invalid construction of epoch date (January 1st, 1970): "
				<< subject
				<< std::setw(13) << "" << std::setprecision(16)
				<< "\n\t\t-> JDN expected: " << epochJDN
				<< "\n\t\t-> JDN recieved: " << subject.toJDN()
				<< "\n\t\t-> JDN divergence: " << (subject.toJDN() - epochJDN)
				<< " days\n"
				<< std::endl;

			FAIL();
		}

		// Confirm initial time
		if ((subject.hour() != 0Ui8) || (subject.minute() != 0Ui8) || (subject.second() != 0Ui8)) {
			std::cout
				<< std::setw(13) << "[ FAILURE  ] "
				<< "Invalid initial epoch time (00:00:00 AM): "
				<< subject
				<< std::setw(13) << "" << std::setprecision(16)
				<< "\n\t\t-> JDN expected: " << epochJDN
				<< "\n\t\t-> JDN recieved: " << subject.toJDN()
				<< "\n\t\t-> JDN divergence: " << (subject.toJDN() - epochJDN)
				<< " days\n"
				<< std::endl;

			FAIL();
		}

		std::cout
			<< std::setw(13) << "[ TEST MSG ] "
			<< "Testing dates "
			<< subject.datetimeStr(Datetime::DateFormat::STANDARD)
			<< " through "
			<< Datetime{ Datetime::MAX_JDN }.datetimeStr(Datetime::DateFormat::STANDARD)
			<< std::endl;

		uint32_t validationCount{ 0 };

		Datetime::JDN lastJDN{ (Datetime::EPOCH_JDN - (Datetime::JDN)1.) };
		Datetime::JDN expectedJDN{ 0. };

		const Duration displace{ 1. };// Duration (1 days)

		// Loop through all possible dates and check for inconsistencies
		while (validationCount != REPRESENTABLE_COUNT) {

			expectedJDN = (lastJDN + (Datetime::JDN)1.);

			// Confirm subject JDN is just one after the previous
			if (subject.toJDN() != expectedJDN) {
				std::cout
					<< std::setw(13) << "[ FAILURE  ] "
					<< "JDN divergence located at '"
					<< subject.dateStr(Datetime::DateFormat::STANDARD)
					<< "' date:"
					<< std::setw(13) << "" << std::setprecision(16)
					<< "\n\t\t-> JDN expected: " << expectedJDN
					<< " (" << Datetime{ expectedJDN }.dateStr(Datetime::DateFormat::STANDARD) << ")"
					<< "\n\t\t-> JDN recieved: " << subject.toJDN()
					<< " (" << Datetime{ subject.toJDN() }.dateStr(Datetime::DateFormat::STANDARD) << ")"
					<< "\n\t\t-> JDN divergence: " << (expectedJDN - subject.toJDN())
					<< " days"
					<< '\n' << std::endl;

				FAIL();
			}

			// Update loop controls
			lastJDN = expectedJDN;
			subject.displace(displace);
			++validationCount;

		}
	}

}
